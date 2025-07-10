
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_LBS_C)

#include "ble_lbs_c_extended.h"
#include "ble_db_discovery.h"
#include "ble_types.h"
#include "ble_srv_common.h"
#include "ble_gattc.h"
#define NRF_LOG_MODULE_NAME ble_lbs_c
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define TX_BUFFER_MASK         0x07                  
#define TX_BUFFER_SIZE         (TX_BUFFER_MASK + 1)  

#define WRITE_MESSAGE_LENGTH   BLE_CCCD_VALUE_LEN    
#define WRITE_MESSAGE_LENGTH   BLE_CCCD_VALUE_LEN    

typedef enum
{
    READ_REQ,  
    WRITE_REQ  
} tx_request_t;


typedef struct
{
    uint8_t                  gattc_value[WRITE_MESSAGE_LENGTH];  
    ble_gattc_write_params_t gattc_params;                       
} write_params_t;


typedef struct
{
    uint16_t     conn_handle;  
    tx_request_t type;         
    union
    {
        uint16_t       read_handle;  
        write_params_t write_req;    
    } req;
} tx_message_t;


static tx_message_t m_tx_buffer[TX_BUFFER_SIZE];  
static uint32_t     m_tx_insert_index = 0;        
static uint32_t     m_tx_index = 0;               



static void tx_buffer_process(void)
{
    if (m_tx_index != m_tx_insert_index)
    {
        uint32_t err_code;

        if (m_tx_buffer[m_tx_index].type == READ_REQ)
        {
            err_code = sd_ble_gattc_read(m_tx_buffer[m_tx_index].conn_handle,
                                         m_tx_buffer[m_tx_index].req.read_handle,
                                         0);
        }
        else
        {
            err_code = sd_ble_gattc_write(m_tx_buffer[m_tx_index].conn_handle,
                                          &m_tx_buffer[m_tx_index].req.write_req.gattc_params);
        }
        if (err_code == NRF_SUCCESS)
        {
            NRF_LOG_DEBUG("SD Read/Write API returns Success..");
            m_tx_index++;
            m_tx_index &= TX_BUFFER_MASK;
        }
        else
        {
            NRF_LOG_DEBUG("SD Read/Write API returns error. This message sending will be "
                "attempted again..");
        }
    }
}



static void on_write_rsp(ble_lbs_c_t * p_ble_lbs_c, ble_evt_t const * p_ble_evt)
{
    
    if (p_ble_lbs_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }
    
    tx_buffer_process();
}



static void on_hvx(ble_lbs_c_t * p_ble_lbs_c, ble_evt_t const * p_ble_evt)
{
    
    if (p_ble_lbs_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }
    
    if (p_ble_evt->evt.gattc_evt.params.hvx.handle == p_ble_lbs_c->peer_lbs_db.button_handle)
    {
        if (p_ble_evt->evt.gattc_evt.params.hvx.len == 1)
        {
            ble_lbs_c_evt_t ble_lbs_c_evt;

            ble_lbs_c_evt.evt_type                   = BLE_LBS_C_EVT_BUTTON_NOTIFICATION;
            ble_lbs_c_evt.conn_handle                = p_ble_lbs_c->conn_handle;
            ble_lbs_c_evt.params.button.button_state = p_ble_evt->evt.gattc_evt.params.hvx.data[0];
            p_ble_lbs_c->evt_handler(p_ble_lbs_c, &ble_lbs_c_evt);
        }
    }
}



static void on_disconnected(ble_lbs_c_t * p_ble_lbs_c, ble_evt_t const * p_ble_evt)
{
    if (p_ble_lbs_c->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ble_lbs_c->conn_handle                    = BLE_CONN_HANDLE_INVALID;
        p_ble_lbs_c->peer_lbs_db.button_cccd_handle = BLE_GATT_HANDLE_INVALID;
        p_ble_lbs_c->peer_lbs_db.button_handle      = BLE_GATT_HANDLE_INVALID;
        p_ble_lbs_c->peer_lbs_db.led_handle         = BLE_GATT_HANDLE_INVALID;
        p_ble_lbs_c->peer_lbs_db.led_color_handle   = BLE_GATT_HANDLE_INVALID;
    }
}


void ble_lbs_on_db_disc_evt(ble_lbs_c_t * p_ble_lbs_c, ble_db_discovery_evt_t const * p_evt)
{
    
    if (p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE &&
        p_evt->params.discovered_db.srv_uuid.uuid == LBS_UUID_SERVICE &&
        p_evt->params.discovered_db.srv_uuid.type == p_ble_lbs_c->uuid_type)
    {
        ble_lbs_c_evt_t evt;

        evt.evt_type    = BLE_LBS_C_EVT_DISCOVERY_COMPLETE;
        evt.conn_handle = p_evt->conn_handle;

        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            const ble_gatt_db_char_t * p_char = &(p_evt->params.discovered_db.charateristics[i]);
            switch (p_char->characteristic.uuid.uuid)
            {
                case LBS_UUID_LED_CHAR:
                    evt.params.peer_db.led_handle = p_char->characteristic.handle_value;
                    break;
                case LBS_UUID_LED_COL_CHAR:
                    evt.params.peer_db.led_color_handle = p_char->characteristic.handle_value;
                    break;
                case LBS_UUID_BUTTON_CHAR:
                    evt.params.peer_db.button_handle      = p_char->characteristic.handle_value;
                    evt.params.peer_db.button_cccd_handle = p_char->cccd_handle;
                    break;

                default:
                    break;
            }
        }

        NRF_LOG_DEBUG("Led Button Service discovered at peer.");
        
        if (p_ble_lbs_c->conn_handle != BLE_CONN_HANDLE_INVALID)
        {
            if ((p_ble_lbs_c->peer_lbs_db.led_handle         == BLE_GATT_HANDLE_INVALID)&&
                (p_ble_lbs_c->peer_lbs_db.led_color_handle   == BLE_GATT_HANDLE_INVALID)&&
                (p_ble_lbs_c->peer_lbs_db.button_handle      == BLE_GATT_HANDLE_INVALID)&&
                (p_ble_lbs_c->peer_lbs_db.button_cccd_handle == BLE_GATT_HANDLE_INVALID))
            {
                p_ble_lbs_c->peer_lbs_db = evt.params.peer_db;
            }
        }

        p_ble_lbs_c->evt_handler(p_ble_lbs_c, &evt);

    }
}


uint32_t ble_lbs_c_init(ble_lbs_c_t * p_ble_lbs_c, ble_lbs_c_init_t * p_ble_lbs_c_init)
{
    uint32_t      err_code;
    ble_uuid_t    lbs_uuid;
    ble_uuid128_t lbs_base_uuid = {LBS_UUID_BASE};

    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c);
    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c_init);
    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c_init->evt_handler);

    p_ble_lbs_c->peer_lbs_db.button_cccd_handle = BLE_GATT_HANDLE_INVALID;
    p_ble_lbs_c->peer_lbs_db.button_handle      = BLE_GATT_HANDLE_INVALID;
    p_ble_lbs_c->peer_lbs_db.led_handle         = BLE_GATT_HANDLE_INVALID;
    p_ble_lbs_c->peer_lbs_db.led_color_handle   = BLE_GATT_HANDLE_INVALID;
    p_ble_lbs_c->conn_handle                    = BLE_CONN_HANDLE_INVALID;
    p_ble_lbs_c->evt_handler                    = p_ble_lbs_c_init->evt_handler;

    err_code = sd_ble_uuid_vs_add(&lbs_base_uuid, &p_ble_lbs_c->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    VERIFY_SUCCESS(err_code);

    lbs_uuid.type = p_ble_lbs_c->uuid_type;
    lbs_uuid.uuid = LBS_UUID_SERVICE;

    return ble_db_discovery_evt_register(&lbs_uuid);
}

void ble_lbs_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_lbs_c_t * p_ble_lbs_c = (ble_lbs_c_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTC_EVT_HVX:
            on_hvx(p_ble_lbs_c, p_ble_evt);
            break;

        case BLE_GATTC_EVT_WRITE_RSP:
            on_write_rsp(p_ble_lbs_c, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_ble_lbs_c, p_ble_evt);
            break;

        default:
            break;
    }
}



static uint32_t cccd_configure(uint16_t conn_handle, uint16_t handle_cccd, bool enable)
{
    NRF_LOG_DEBUG("Configuring CCCD. CCCD Handle = %d, Connection Handle = %d",
        handle_cccd,conn_handle);

    tx_message_t * p_msg;
    uint16_t       cccd_val = enable ? BLE_GATT_HVX_NOTIFICATION : 0;

    p_msg              = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    p_msg->req.write_req.gattc_params.handle   = handle_cccd;
    p_msg->req.write_req.gattc_params.len      = WRITE_MESSAGE_LENGTH;
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;
    p_msg->req.write_req.gattc_value[0]        = LSB_16(cccd_val);
    p_msg->req.write_req.gattc_value[1]        = MSB_16(cccd_val);
    p_msg->conn_handle                         = conn_handle;
    p_msg->type                                = WRITE_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_lbs_c_button_notif_enable(ble_lbs_c_t * p_ble_lbs_c)
{
    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c);

    if (p_ble_lbs_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    return cccd_configure(p_ble_lbs_c->conn_handle,
                          p_ble_lbs_c->peer_lbs_db.button_cccd_handle,
                          true);
}


uint32_t ble_lbs_led_status_send(ble_lbs_c_t * p_ble_lbs_c, uint8_t status)
{
    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c);

    if (p_ble_lbs_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    NRF_LOG_DEBUG("writing LED status 0x%x", status);

    tx_message_t * p_msg;

    p_msg              = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    p_msg->req.write_req.gattc_params.handle   = p_ble_lbs_c->peer_lbs_db.led_handle;
    p_msg->req.write_req.gattc_params.len      = sizeof(status);
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_CMD;
    p_msg->req.write_req.gattc_value[0]        = status;
    p_msg->conn_handle                         = p_ble_lbs_c->conn_handle;
    p_msg->type                                = WRITE_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_lbs_led_color_send(ble_lbs_c_t * p_ble_lbs_c, uint8_t *colors)
{
    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c);

    if (p_ble_lbs_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_ble_lbs_c->peer_lbs_db.led_color_handle == BLE_GATT_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    NRF_LOG_INFO("writing LED color %i, %i, %i", colors[0], colors[1], colors[2]);

    tx_message_t * p_msg;

    p_msg              = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    p_msg->req.write_req.gattc_params.handle   = p_ble_lbs_c->peer_lbs_db.led_color_handle;
    p_msg->req.write_req.gattc_params.len      = 4;
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_CMD;
    memcpy(p_msg->req.write_req.gattc_value, colors, 3);
    p_msg->conn_handle                         = p_ble_lbs_c->conn_handle;
    p_msg->type                                = WRITE_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_lbs_c_handles_assign(ble_lbs_c_t    * p_ble_lbs_c,
                                  uint16_t         conn_handle,
                                  const lbs_db_t * p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_ble_lbs_c);

    p_ble_lbs_c->conn_handle = conn_handle;
    if (p_peer_handles != NULL)
    {
        p_ble_lbs_c->peer_lbs_db = *p_peer_handles;
    }
    return NRF_SUCCESS;
}

#endif 
