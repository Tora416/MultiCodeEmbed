
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_LBS)
#include "ble_lbs_extended.h"
#include "ble_srv_common.h"



static void on_write(ble_lbs_t * p_lbs, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if ((p_evt_write->handle == p_lbs->led_char_handles.value_handle)
        && (p_evt_write->len == 1)
        && (p_lbs->led_write_handler != NULL))
    {
        p_lbs->led_write_handler(p_ble_evt->evt.gap_evt.conn_handle, p_lbs, p_evt_write->data[0]);
    }
    else if ((p_evt_write->handle == p_lbs->led_col_char_handles.value_handle)
        && (p_evt_write->len == 4)
        && (p_lbs->led_col_write_handler != NULL))
    {
        uint32_t color = p_evt_write->data[0] << 16 | p_evt_write->data[1] << 8 | p_evt_write->data[2] << 0;
        p_lbs->led_col_write_handler(p_ble_evt->evt.gap_evt.conn_handle, p_lbs, color);
    }
}


void ble_lbs_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_lbs_t * p_lbs = (ble_lbs_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
            on_write(p_lbs, p_ble_evt);
            break;

        default:
            
            break;
    }
}


uint32_t ble_lbs_init(ble_lbs_t * p_lbs, const ble_lbs_init_t * p_lbs_init)
{
    uint32_t              err_code;
    ble_uuid_t            ble_uuid;
    ble_add_char_params_t add_char_params;

    
    p_lbs->led_write_handler = p_lbs_init->led_write_handler;
    p_lbs->led_col_write_handler = p_lbs_init->led_col_write_handler;

    
    ble_uuid128_t base_uuid = {LBS_UUID_BASE};
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_lbs->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_lbs->uuid_type;
    ble_uuid.uuid = LBS_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_lbs->service_handle);
    VERIFY_SUCCESS(err_code);

    
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = LBS_UUID_BUTTON_CHAR;
    add_char_params.uuid_type         = p_lbs->uuid_type;
    add_char_params.init_len          = sizeof(uint8_t);
    add_char_params.max_len           = sizeof(uint8_t);
    add_char_params.char_props.read   = 1;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access       = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;

    err_code = characteristic_add(p_lbs->service_handle,
                                  &add_char_params,
                                  &p_lbs->button_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid             = LBS_UUID_LED_CHAR;
    add_char_params.uuid_type        = p_lbs->uuid_type;
    add_char_params.init_len         = sizeof(uint8_t);
    add_char_params.max_len          = sizeof(uint8_t);
    add_char_params.char_props.read  = 1;
    add_char_params.char_props.write = 1;

    add_char_params.read_access  = SEC_OPEN;
    add_char_params.write_access = SEC_OPEN;

    err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->led_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid             = LBS_UUID_LED_COL_CHAR;
    add_char_params.uuid_type        = p_lbs->uuid_type;
    add_char_params.init_len         = sizeof(uint32_t);
    add_char_params.max_len          = sizeof(uint32_t);
    add_char_params.char_props.read  = 1;
    add_char_params.char_props.write = 1;

    add_char_params.read_access  = SEC_OPEN;
    add_char_params.write_access = SEC_OPEN;

    err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->led_col_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
}


uint32_t ble_lbs_on_button_change(uint16_t conn_handle, ble_lbs_t * p_lbs, uint8_t button_state)
{
    ble_gatts_hvx_params_t params;
    uint16_t len = sizeof(button_state);

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_NOTIFICATION;
    params.handle = p_lbs->button_char_handles.value_handle;
    params.p_data = &button_state;
    params.p_len  = &len;

    return sd_ble_gatts_hvx(conn_handle, &params);
}
#endif 
