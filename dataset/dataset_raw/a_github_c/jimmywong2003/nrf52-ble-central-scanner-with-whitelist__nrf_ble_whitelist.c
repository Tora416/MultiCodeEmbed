

#include "sdk_common.h"

#include "sdk_config.h"
#include <stdlib.h>

#if 1

#include <string.h>
#include "app_error.h"
#include "nrf_assert.h"
#include "sdk_macros.h"
#include "ble_advdata.h"

#include "nrf_ble_whitelist.h"



static bool m_whitelist_is_running = false;

static ble_gap_addr_t const * m_whitelist_addr_ptrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
static ble_gap_addr_t m_whitelist_addrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
static uint8_t m_addr_cnt = 0;

ret_code_t nrf_ble_whitelist_add(ble_gap_addr_t *addr, uint8_t * whitelist_count)
{

        if (m_addr_cnt >= BLE_GAP_WHITELIST_ADDR_MAX_COUNT)
                return NRF_ERROR_DATA_SIZE;

        for (uint32_t i = 0; i < BLE_GAP_WHITELIST_ADDR_MAX_COUNT; i++)
        {
                if (memcmp(&m_whitelist_addrs[i], addr, sizeof(ble_gap_addr_t))==0)
                {
                        
                        return NRF_ERROR_INVALID_PARAM;
                }
        }

        memcpy(&m_whitelist_addrs[m_addr_cnt], addr, sizeof(ble_gap_addr_t));

        m_addr_cnt++;

        
        *whitelist_count = m_addr_cnt;

        return NRF_SUCCESS;
}

ret_code_t nrf_ble_whitelist_enable(void)
{
        ret_code_t ret;

        m_whitelist_is_running = true;

        if (m_addr_cnt == 0)
        {
                return NRF_ERROR_DATA_SIZE;
        }

        for (uint32_t i = 0; i < BLE_GAP_WHITELIST_ADDR_MAX_COUNT; i++)
        {
                m_whitelist_addr_ptrs[i] = &m_whitelist_addrs[i];
        }

        ret = sd_ble_gap_whitelist_set(m_whitelist_addr_ptrs, m_addr_cnt);
        APP_ERROR_CHECK(ret);

        return NRF_SUCCESS;
}


uint8_t nrf_ble_whitelist_cnt(void)
{
        return m_addr_cnt;
}

ret_code_t nrf_ble_whitelist_clear(void)
{
        ret_code_t ret;
        memset(m_whitelist_addrs, 0, sizeof(m_whitelist_addrs));
        m_addr_cnt = 0;

        ret = sd_ble_gap_whitelist_set(NULL, 0);
        APP_ERROR_CHECK(ret);


        m_whitelist_is_running = false;
        return ret;
}


bool nrf_ble_whitelist_is_running(void)
{
        return m_whitelist_is_running;
}



#endif 
