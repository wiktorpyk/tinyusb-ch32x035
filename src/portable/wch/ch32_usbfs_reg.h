/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Matthew Tran
 * Copyright (c) 2024 hathach
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#ifndef USB_CH32_USBFS_REG_H
#define USB_CH32_USBFS_REG_H

// https://github.com/openwch/ch32v307/pull/90
// https://github.com/openwch/ch32v20x/pull/12
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#endif

#if CFG_TUSB_MCU == OPT_MCU_CH32F20X
  #include <ch32f20x.h>
#elif CFG_TUSB_MCU == OPT_MCU_CH32V103
  #include <ch32v10x.h>
  typedef struct
  {
    __IO uint8_t  BASE_CTRL;
    __IO uint8_t  UDEV_CTRL;
    __IO uint8_t  INT_EN;
    __IO uint8_t  DEV_ADDR;
    __IO uint8_t  Reserve0;
    __IO uint8_t  MIS_ST;
    __IO uint8_t  INT_FG;
    __IO uint8_t  INT_ST;
    __IO uint32_t RX_LEN;
    __IO uint8_t  UEP4_1_MOD;
    __IO uint8_t  UEP2_3_MOD;
    __IO uint8_t  UEP5_6_MOD;
    __IO uint8_t  UEP7_MOD;
    __IO uint32_t UEP0_DMA;
    __IO uint32_t UEP1_DMA;
    __IO uint32_t UEP2_DMA;
    __IO uint32_t UEP3_DMA;
    __IO uint32_t UEP4_DMA;
    __IO uint32_t UEP5_DMA;
    __IO uint32_t UEP6_DMA;
    __IO uint32_t UEP7_DMA;
    __IO uint16_t UEP0_TX_LEN;
    __IO uint8_t  UEP0_TX_CTRL;
    __IO uint8_t  UEP0_RX_CTRL;
    __IO uint16_t UEP1_TX_LEN;
    __IO uint8_t  UEP1_TX_CTRL;
    __IO uint8_t  UEP1_RX_CTRL;
    __IO uint16_t UEP2_TX_LEN;
    __IO uint8_t  UEP2_TX_CTRL;
    __IO uint8_t  UEP2_RX_CTRL;
    __IO uint16_t UEP3_TX_LEN;
    __IO uint8_t  UEP3_TX_CTRL;
    __IO uint8_t  UEP3_RX_CTRL;
    __IO uint16_t UEP4_TX_LEN;
    __IO uint8_t  UEP4_TX_CTRL;
    __IO uint8_t  UEP4_RX_CTRL;
    __IO uint16_t UEP5_TX_LEN;
    __IO uint8_t  UEP5_TX_CTRL;
    __IO uint8_t  UEP5_RX_CTRL;
    __IO uint16_t UEP6_TX_LEN;
    __IO uint8_t  UEP6_TX_CTRL;
    __IO uint8_t  UEP6_RX_CTRL;
    __IO uint16_t UEP7_TX_LEN;
    __IO uint8_t  UEP7_TX_CTRL;
    __IO uint8_t  UEP7_RX_CTRL;
    __IO uint32_t Reserve1;
    __IO uint32_t OTG_CR;
    __IO uint32_t OTG_SR;
  } USBOTG_FS_TypeDef;

  #define USBOTG_FS ((USBOTG_FS_TypeDef *) 0x40023400)
#elif CFG_TUSB_MCU == OPT_MCU_CH32V20X
  #include <ch32v20x.h>
#elif CFG_TUSB_MCU == OPT_MCU_CH32V307
  #include <ch32v30x.h>
  #define USBHD_IRQn OTG_FS_IRQn
#elif CFG_TUSB_MCU == OPT_MCU_CH32X035
  #include <ch32x035.h>
  // CH32X035 has a different register layout per datasheet section 18.2
  // Key differences:
  // - No UEP4_DMA register (UEP4 uses UEP0_DMA buffer)
  // - UEP567_MOD is a single register controlling EP5/6/7
  // - Different register offsets for EP5/6/7
  typedef struct {
    __IO uint8_t  BASE_CTRL;     // 0x40023400
    __IO uint8_t  UDEV_CTRL;     // 0x40023401
    __IO uint8_t  INT_EN;        // 0x40023402
    __IO uint8_t  DEV_ADDR;      // 0x40023403
    uint8_t       RESERVED0;     // 0x40023404
    __IO uint8_t  MIS_ST;        // 0x40023405
    __IO uint8_t  INT_FG;        // 0x40023406
    __IO uint8_t  INT_ST;        // 0x40023407
    __IO uint32_t RX_LEN;        // 0x40023408
    __IO uint8_t  UEP4_1_MOD;    // 0x4002340C
    __IO uint8_t  UEP2_3_MOD;    // 0x4002340D
    __IO uint8_t  UEP567_MOD;    // 0x4002340E (single register for EP5/6/7)
    uint8_t       RESERVED1;     // 0x4002340F
    __IO uint32_t UEP0_DMA;      // 0x40023410
    __IO uint32_t UEP1_DMA;      // 0x40023414
    __IO uint32_t UEP2_DMA;      // 0x40023418
    __IO uint32_t UEP3_DMA;      // 0x4002341C
    __IO uint16_t UEP0_TX_LEN;   // 0x40023420
    __IO uint8_t  UEP0_TX_CTRL;  // 0x40023422 (bits [7:0] of CTRL_H)
    __IO uint8_t  UEP0_RX_CTRL;  // 0x40023422 (bits [15:8] of CTRL_H)
    __IO uint16_t UEP1_TX_LEN;   // 0x40023424
    __IO uint8_t  UEP1_TX_CTRL;  // 0x40023426
    __IO uint8_t  UEP1_RX_CTRL;  // 0x40023426
    __IO uint16_t UEP2_TX_LEN;   // 0x40023428
    __IO uint8_t  UEP2_TX_CTRL;  // 0x4002342A
    __IO uint8_t  UEP2_RX_CTRL;  // 0x4002342A
    __IO uint16_t UEP3_TX_LEN;   // 0x4002342C
    __IO uint8_t  UEP3_TX_CTRL;  // 0x4002342E
    __IO uint8_t  UEP3_RX_CTRL;  // 0x4002342E
    __IO uint16_t UEP4_TX_LEN;   // 0x40023430
    __IO uint8_t  UEP4_TX_CTRL;  // 0x40023432
    __IO uint8_t  UEP4_RX_CTRL;  // 0x40023432
    uint32_t      RESERVED2[8];  // 0x40023434-0x40023450
    __IO uint32_t UEP5_DMA;      // 0x40023454
    __IO uint32_t UEP6_DMA;      // 0x40023458
    __IO uint32_t UEP7_DMA;      // 0x4002345C
    uint32_t      RESERVED3;     // 0x40023460
    __IO uint16_t UEP5_TX_LEN;   // 0x40023464
    __IO uint8_t  UEP5_TX_CTRL;  // 0x40023466
    __IO uint8_t  UEP5_RX_CTRL;  // 0x40023466
    __IO uint16_t UEP6_TX_LEN;   // 0x40023468
    __IO uint8_t  UEP6_TX_CTRL;  // 0x4002346A
    __IO uint8_t  UEP6_RX_CTRL;  // 0x4002346A
    __IO uint16_t UEP7_TX_LEN;   // 0x4002346C
    __IO uint8_t  UEP7_TX_CTRL;  // 0x4002346E
    __IO uint8_t  UEP7_RX_CTRL;  // 0x4002346E
    __IO uint32_t UEPX_MOD;      // 0x40023470
  } USBOTG_FS_TypeDef;

  #define USBOTG_FS ((USBOTG_FS_TypeDef *) USBFS_BASE)
  #define USBHD_IRQn USBFS_IRQn
  // Compatibility aliases for code that expects separate EP5_6_MOD and EP7_MOD
  #define UEP5_6_MOD UEP567_MOD
  #define UEP7_MOD UEP567_MOD
#endif

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

// BASE_CTRL (R8_BASE_CTRL) - Per datasheet section 18.2.1.1
#define USBFS_CTRL_DMA_EN    (1 << 0)  // RB_UC_DMA_EN: DMA enable
#define USBFS_CTRL_CLR_ALL   (1 << 1)  // RB_UC_CLR_ALL: Clear FIFO and interrupt flags
#define USBFS_CTRL_RESET_SIE (1 << 2)  // RB_UC_RST_SIE: Reset USB protocol processor
#define USBFS_CTRL_INT_BUSY  (1 << 3)  // RB_UC_INT_BUSY: Auto pause on transfer complete
// Bits [5:4] are RB_SYS_MODE (test mode in host mode)
#define USBFS_CTRL_LOW_SPEED (1 << 6)  // RB_UC_LOW_SPEED: Low speed enable
#define USBFS_CTRL_HOST_MODE (1 << 7)  // RB_UC_HOST_MOD: 1=Host, 0=Device

// INT_EN
#define USBFS_INT_EN_BUS_RST  (1 << 0)
#define USBFS_INT_EN_DETECT   (1 << 0)
#define USBFS_INT_EN_TRANSFER (1 << 1)
#define USBFS_INT_EN_SUSPEND  (1 << 2)
#define USBFS_INT_EN_HST_SOF  (1 << 3)
#define USBFS_INT_EN_FIFO_OV  (1 << 4)
#define USBFS_INT_EN_DEV_NAK  (1 << 6)
#define USBFS_INT_EN_DEV_SOF  (1 << 7)

// INT_FG
#define USBFS_INT_FG_BUS_RST  (1 << 0)
#define USBFS_INT_FG_DETECT   (1 << 0)
#define USBFS_INT_FG_TRANSFER (1 << 1)
#define USBFS_INT_FG_SUSPEND  (1 << 2)
#define USBFS_INT_FG_HST_SOF  (1 << 3)
#define USBFS_INT_FG_FIFO_OV  (1 << 4)
#define USBFS_INT_FG_SIE_FREE (1 << 5)
#define USBFS_INT_FG_TOG_OK   (1 << 6)
#define USBFS_INT_FG_IS_NAK   (1 << 7)

// INT_ST
#define USBFS_INT_ST_MASK_UIS_ENDP(x)  (((x) >> 0) & 0x0F)
#define USBFS_INT_ST_MASK_UIS_TOKEN(x) (((x) >> 4) & 0x03)

// UDEV_CTRL
#define USBFS_UDEV_CTRL_PORT_EN   (1 << 0)
#define USBFS_UDEV_CTRL_GP_BIT    (1 << 1)
#define USBFS_UDEV_CTRL_LOW_SPEED (1 << 2)
#define USBFS_UDEV_CTRL_DM_PIN    (1 << 4)
#define USBFS_UDEV_CTRL_DP_PIN    (1 << 5)
#define USBFS_UDEV_CTRL_PD_DIS    (1 << 7)

// TX_CTRL (EPn_T_RES) - Transmit response control, bits [1:0] per datasheet
#define USBFS_EP_T_RES_MASK  (3 << 0)   // Bits [1:0]: transmit response
#define USBFS_EP_T_RES_ACK   (0 << 0)   // 00: Expect ACK
#define USBFS_EP_T_RES_NYET  (1 << 0)   // 01: Expect NYET (not valid for EP0)
#define USBFS_EP_T_RES_NAK   (2 << 0)   // 10: Expect NAK or busy
#define USBFS_EP_T_RES_STALL (3 << 0)   // 11: Expect STALL or error
#define USBFS_EP_T_TOG       (1 << 6)   // Bit 6: Sync trigger (EP*_T_TOG)
#define USBFS_EP_T_AUTO_TOG  (1 << 4)   // Bit 4: Auto-toggle enable (EP*_TOG_AUTO)

// RX_CTRL (EPn_R_RES) - Receive response control, bits [3:2] per datasheet
#define USBFS_EP_R_RES_MASK  (3 << 2)   // Bits [3:2]: receive response
#define USBFS_EP_R_RES_ACK   (0 << 2)   // 00: Data ready, expect ACK
#define USBFS_EP_R_RES_NYET  (1 << 2)   // 01: Answer NYET (not valid for EP0)
#define USBFS_EP_R_RES_NAK   (2 << 2)   // 10: Response NAK or busy
#define USBFS_EP_R_RES_STALL (3 << 2)   // 11: Answer STALL or error
#define USBFS_EP_R_TOG       (1 << 7)   // Bit 7: Sync trigger (EP*_R_TOG)
#define USBFS_EP_R_AUTO_TOG  (1 << 4)   // Bit 4: Auto-toggle enable (shared with TX)

// token PID
#define PID_OUT   0
#define PID_SOF   1
#define PID_IN    2
#define PID_SETUP 3

#endif // USB_CH32_USBFS_REG_H
