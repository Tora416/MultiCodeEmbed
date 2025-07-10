

#include "nrf_dfu_flash.h"
#include "nrf_dfu_types.h"

#include "nrf_fstorage.h"
#include "nrf_fstorage_sd.h"
#include "nrf_fstorage_nvmc.h"


#define NRF_LOG_MODULE_NAME nrf_dfu_flash
#include "nrf_log.h"

#if NRF_DFU_FLASH_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL BLE_SCAN_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR BLE_SCAN_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR BLE_SCAN_CONFIG_DEBUG_COLOR
#else 
#define NRF_LOG_LEVEL 4
#endif 
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


void dfu_fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);


NRF_FSTORAGE_DEF(nrf_fstorage_t m_fs) =
{
        .evt_handler = dfu_fstorage_evt_handler,
        .start_addr  = MBR_SIZE,
        .end_addr    = BOOTLOADER_SETTINGS_ADDRESS + BOOTLOADER_SETTINGS_PAGE_SIZE
};

static uint32_t m_flash_operations_pending;

void dfu_fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{
        if (NRF_LOG_ENABLED && (m_flash_operations_pending > 0))
        {
                m_flash_operations_pending--;
        }

        if (p_evt->result == NRF_SUCCESS)
        {
                NRF_LOG_DEBUG("Flash %s success: addr=%p, pending %d",
                              (p_evt->id == NRF_FSTORAGE_EVT_WRITE_RESULT) ? "write" : "erase",
                              p_evt->addr, m_flash_operations_pending);
        }
        else
        {
                NRF_LOG_DEBUG("Flash %s failed (0x%x): addr=%p, len=0x%x bytes, pending %d",
                              (p_evt->id == NRF_FSTORAGE_EVT_WRITE_RESULT) ? "write" : "erase",
                              p_evt->result, p_evt->addr, p_evt->len, m_flash_operations_pending);
        }

        if (p_evt->p_param)
        {
                
                ((nrf_dfu_flash_callback_t)(p_evt->p_param))((void*)p_evt->p_src);
                
        }
}


ret_code_t nrf_dfu_flash_init(bool sd_irq_initialized)
{
        nrf_fstorage_api_t * p_api_impl;

        
#if defined(BLE_STACK_SUPPORT_REQD) || defined(ANT_STACK_SUPPORT_REQD)
        if (sd_irq_initialized)
        {
                NRF_LOG_DEBUG("Initializing nrf_fstorage_sd backend.");
                p_api_impl = &nrf_fstorage_sd;
        }
        else
#endif
        {
                NRF_LOG_DEBUG("Initializing nrf_fstorage_nvmc backend.");
                p_api_impl = &nrf_fstorage_nvmc;
        }



        return nrf_fstorage_init(&m_fs, p_api_impl, NULL);
}


ret_code_t nrf_dfu_flash_store(uint32_t dest,
                               void const * p_src,
                               uint32_t len,
                               nrf_dfu_flash_callback_t callback)
{
        ret_code_t rc;

        NRF_LOG_DEBUG("nrf_fstorage_write(addr=%p, src=%p, len=%d bytes), queue usage: %d",
                      dest, p_src, len, m_flash_operations_pending);

        
        rc = nrf_fstorage_write(&m_fs, dest, p_src, len, (void *)callback);
        

        if ((NRF_LOG_ENABLED) && (rc == NRF_SUCCESS))
        {
                m_flash_operations_pending++;
        }
        else
        {
                NRF_LOG_WARNING("nrf_fstorage_write() failed with error 0x%x.", rc);
        }

        return rc;
}


ret_code_t nrf_dfu_flash_erase(uint32_t page_addr,
                               uint32_t num_pages,
                               nrf_dfu_flash_callback_t callback)
{
        ret_code_t rc;

        NRF_LOG_DEBUG("nrf_fstorage_erase(addr=0x%p, len=%d pages), queue usage: %d",
                      page_addr, num_pages, m_flash_operations_pending);

        
        rc = nrf_fstorage_erase(&m_fs, page_addr, num_pages, (void *)callback);
        

        if ((NRF_LOG_ENABLED) && (rc == NRF_SUCCESS))
        {
                m_flash_operations_pending++;
        }
        else
        {
                NRF_LOG_WARNING("nrf_fstorage_erase() failed with error 0x%x.", rc);
        }

        return rc;
}
