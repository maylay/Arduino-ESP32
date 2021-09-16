#ifndef LGFX_TOUCH_COMMON_HPP_
#define LGFX_TOUCH_COMMON_HPP_

#include <cstdint>
#include <type_traits>

#include "../lgfx_common.hpp"

namespace lgfx
{
 inline namespace v0
 {
//----------------------------------------------------------------------------
  struct TouchCommon
  {
    union {
      struct {
        std::int_fast8_t spi_host; // ESP32:spi_host_device_t VSPI_HOST or HSPI_HOST
        std::int_fast16_t spi_sclk;
        std::int_fast16_t spi_mosi;
        std::int_fast16_t spi_miso;
        std::int_fast16_t spi_cs;
      };
      struct {
        std::int_fast8_t i2c_port; // ESP32:i2c_port_t I2C_NUM_0 or I2C_NUM_1
        std::int_fast16_t i2c_scl;
        std::int_fast16_t i2c_sda;
        std::int_fast16_t i2c_addr;
        //
      };
    };

    std::int_fast16_t gpio_int = -1;
    std::int32_t freq = 1000000;
    std::uint32_t x_min = 0;
    std::uint32_t x_max = 3600;
    std::uint32_t y_min = 0;
    std::uint32_t y_max = 3600;
    bool bus_shared = false;

    TouchCommon()
    : spi_host(0)
    , spi_sclk(-1)
    , spi_mosi(-1)
    , spi_miso(-1)
    , spi_cs  (-1)
    {}

    inline bool isSPI(void) const { return spi_cs >= 0; }

    virtual bool init(void) = 0;
    virtual void wakeup(void) {}
    virtual void sleep(void) {}
    virtual std::uint_fast8_t getTouch(touch_point_t* tp, std::int_fast8_t number) = 0;

  protected:
    bool _inited = false;
  };

//----------------------------------------------------------------------------
 }
}
#endif
