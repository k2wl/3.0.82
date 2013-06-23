/************************************************************************************************/
/*                                                                                              */
/*  Copyright 2010  Broadcom Corporation                                                        */
/*                                                                                              */
/*     Unless you and Broadcom execute a separate written software license agreement governing  */
/*     use of this software, this software is licensed to you under the terms of the GNU        */
/*     General Public License version 2 (the GPL), available at                                 */
/*                                                                                              */
/*          http://www.broadcom.com/licenses/GPLv2.php                                          */
/*                                                                                              */
/*     with the following added to such license:                                                */
/*                                                                                              */
/*     As a special exception, the copyright holders of this software give you permission to    */
/*     link this software with independent modules, and to copy and distribute the resulting    */
/*     executable under terms of your choice, provided that you also meet, for each linked      */
/*     independent module, the terms and conditions of the license of that module.              */
/*     An independent module is a module which is not derived from this software.  The special  */
/*     exception does not apply to any modifications of the software.                           */
/*                                                                                              */
/*     Notwithstanding the above, under no circumstances may you combine this software in any   */
/*     way with any other Broadcom software provided under a license other than the GPL,        */
/*     without Broadcom's express prior written consent.                                        */
/*                                                                                              */
/************************************************************************************************/
#include <mach/pinmux.h>
#include <mach/rdb/brcm_rdb_padctrlreg.h>
#include <mach/rdb/brcm_rdb_sysmap.h>
#include <linux/kernel.h>
#include <asm/bug.h>

#define	PIN_DESC(ball, alt1, alt2, alt3, alt4, d_gpio_num, d_flags)				\
	[PN_##ball] = {							\
		.name		=	PN_##ball,			\
		.reg_offset	=	PADCTRLREG_##ball##_OFFSET,	\
		.f_tbl		=	{				\
			PF_##alt1, PF_##alt2,				\
			PF_##alt3, PF_##alt4,				\
		},							\
		.gpio_num	= (d_gpio_num),				\
		.flags		= (d_flags),				\
	}

#define NONE   PIN_DESC_GPIO_NUM_NONE

// TODO when done, check for VC-controlled pins which don't have "VC_" prefixes!

/*
 * Capri chip-level pin description table
 */
/* Important!!! please keep this table in pin order defined by enum PIN_NAME */
static const struct pin_desc pin_desc_tbl[PN_MAX] = {
	PIN_DESC(ADCSYNC, GPEN09, RESERVED, RESERVED, GPIO_024, 24,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(BAT_RM, BAT_RM, RESERVED, RESERVED, DEBUG_BUS15, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(BSC1_SCL, BSC1_SCL, RESERVED, RESERVED, SPARE_07, NONE,
		 PIN_DESC_FLAGS_I2C),
	PIN_DESC(BSC1_SDA, BSC1_SDA, RESERVED, RESERVED, SPARE_08, NONE,
		 PIN_DESC_FLAGS_I2C),
	PIN_DESC(BSC2_SCL, BSC2_SCL, RESERVED, RESERVED, SPARE_09, NONE,
		 PIN_DESC_FLAGS_I2C),
	PIN_DESC(BSC2_SDA, BSC2_SDA, RESERVED, RESERVED, SPARE_10, NONE,
		 PIN_DESC_FLAGS_I2C),
	PIN_DESC(CLASSGPWR, CLASSGPWR, PC3, RESERVED, GPIO_190, 190,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(CLK_CX8, CLK_CX8, RESERVED, RESERVED, GPIO_041, 41,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(CLKOUT_0, CLKOUT_0, RESERVED, RESERVED, SPARE_11, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(CLKOUT_1, CLKOUT_1, PWM_O_1, VC_GPCLK_2, GPIO_180, 180,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(CLKOUT_2, CLKOUT_2, PWM_O_2, VC_GPCLK_0, GPIO_181, 181,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(CLKOUT_3, CLKOUT_3, PWM_O_3, VC_GPCLK_1, GPIO_182, 182,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(CLKREQ_IN_0, CLKREQ_IN_0, THERMAL_SHUTDOWN, RESERVED, GPIO_178,
		 178, PIN_DESC_FLAGS_NONE),
	PIN_DESC(CLKREQ_IN_1, CLKREQ_IN_1, PWM_O_0, VC_TE0, GPIO_179, 179,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(CWS_SYS_REQ1, CWS_SYS_REQ1, PWM_O_4, VC_UTXD, GPIO_183, 183,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(CWS_SYS_REQ2, CWS_SYS_REQ2, VC_CPG0, VC_URXD, GPIO_184, 184,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(CWS_SYS_REQ3, CWS_SYS_REQ3, CLKMON, VC_GPIO_6, GPIO_185, 185,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(DIGMIC1_CLK, DIGMIC1_CLK, RESERVED, RESERVED, GPIO_186, 186,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(DIGMIC1_DQ, DIGMIC1_DQ, RESERVED, RESERVED, GPIO_187, 187,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(DIGMIC2_CLK, DIGMIC2_CLK, PWM_O_5, VC_PWM_0, GPIO_188, 188,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(DIGMIC2_DQ, DIGMIC2_DQ, PWM_O_0, VC_PWM_1, GPIO_189, 189,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(GPEN13, GPEN13, RESERVED, RESERVED, GPIO_028, 28,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(GPEN14, GPEN14, RESERVED, RESERVED, GPIO_029, 29,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(GPEN15, GPEN15, RESERVED, RESERVED, GPIO_030, 30,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(GPIO00, DBI_C_CSX, VC_TE1, USB1PFT, GPIO_000, 0,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(GPIO01, VC_GPIO_1, VC_TE0, VC_TE2, GPIO_001, 1,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(GPIO02, VC_GPIO_2, CIR_TX, MDIO, GPIO_002, 2,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO03, VC_GPIO_3, CIR_RX, MDC, GPIO_003, 3,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO04, VC_GPIO_4, USB1PON, IRD_OSC_0, GPIO_004, 4,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO05, VC_GPIO_5, PWM_O_1, IRD_OSC_1, GPIO_005, 5,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO06, VC_GPIO_6, VC_PWM_0, PWM_O_2, GPIO_006, 6,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2),
	PIN_DESC(GPIO07, VC_GPIO_7, VC_PWM_1, PWM_O_3, GPIO_007, 7,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2),
	PIN_DESC(GPIO08, DBI_C_DIN, VC_CPG0, SSP3_FS, GPIO_008, 8,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(GPIO09, DBI_C_DOUT, VC_CPG1, SSP3_CLK, GPIO_009, 9,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(GPIO10, VC_TE0, PWM_O_4, SSP3_RXD, GPIO_010, 10,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO11, VC_TE1, PWM_O_5, SSP3_TXD, GPIO_011, 11,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO12, RESERVED, RESERVED, MDIO, GPIO_012, 12,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(GPIO13, VC_TESTDEBUG_CLK, CLKMON, MDC, GPIO_013, 13,
		 PIN_DESC_FLAGS_VC_1),
	PIN_DESC(GPIO14, CLKMON, VC_GPIO_5, RFGPO_4, GPIO_014, 14,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(GPS_PABLANK, GPEN12, RESERVED, RESERVED, GPIO_025, 25,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(GPS_TMARK, GPEN10, RESERVED, RESERVED, GPIO_027, 27,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(HDMI_SCL, HDMI_SCL, BSC3_SCL, RESERVED, SPARE_05, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(HDMI_SDA, HDMI_SDA, BSC3_SDA, RESERVED, SPARE_06, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(IC_DM, IC_DM, VC_URXD, OSC2_OUT, GPIO_177, 177,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(IC_DP, IC_DP, VC_UTXD, OSC1_OUT, GPIO_176, 176,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(KP_COL_IP_0, KP_COL_IP_0, VC_GPIO_2, CADATA, GPIO_061, 61,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(KP_COL_IP_1, KP_COL_IP_1, VC_GPIO_3, CAFLAG, GPIO_062, 62,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(KP_COL_IP_2, KP_COL_IP_2, SSP0_RXD, CAREADY, GPIO_063, 63,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(KP_COL_IP_3, KP_COL_IP_3, SSP0_TXD, CAWAKE, GPIO_064, 64,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(KP_ROW_OP_0, KP_ROW_OP_0, VC_GPCLK_2, ACDATA, GPIO_057, 57,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(KP_ROW_OP_1, KP_ROW_OP_1, VC_GPIO_1, ACFLAG, GPIO_058, 58,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(KP_ROW_OP_2, KP_ROW_OP_2, SSP0_CLK, ACREADY, GPIO_059, 59,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(KP_ROW_OP_3, KP_ROW_OP_3, SSP0_FS, ACWAKE, GPIO_060, 60,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(LCD_B_0, LCD_B_0, DBI_C_SCL, AVEIN_VID0, GPIO_169, 169,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_1, LCD_B_1, DBI_C_CSX, AVEIN_VID1, GPIO_168, 168,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_2, LCD_B_2, DBI_B_D_CX, AVEIN_VID2, GPIO_167, 167,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_3, LCD_B_3, DBI_B_D0, AVEIN_VID3, GPIO_166, 166,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_4, LCD_B_4, DBI_B_D1, AVEIN_VID4, GPIO_165, 165,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_5, LCD_B_5, DBI_B_D2, AVEIN_VID5, GPIO_164, 164,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_6, LCD_B_6, DBI_B_D3, AVEIN_VID6, GPIO_163, 163,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_B_7, LCD_B_7, DBI_B_D4, AVEIN_VID7, GPIO_162, 162,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_0, LCD_G_0, DBI_C_DOUT, AVEIN_VID8, GPIO_161, 161,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_1, LCD_G_1, DBI_C_DIN, AVEIN_VID9, GPIO_160, 160,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_2, LCD_G_2, DBI_B_D5, AVEIN_VID10, GPIO_159, 159,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_3, LCD_G_3, DBI_B_D6, AVEIN_VID11, GPIO_158, 158,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_4, LCD_G_4, DBI_B_D7, AVEIN_VID12, GPIO_157, 157,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_5, LCD_G_5, DBI_B_D8, AVEIN_VID13, GPIO_156, 156,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_6, LCD_G_6, DBI_B_D9, AVEIN_VID14, GPIO_155, 155,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_G_7, LCD_G_7, DBI_B_D10, AVEIN_VID15, GPIO_154, 154,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_HSYNC, LCD_HSYNC, DBI_B_RESX, AVEIN_HSYNC, GPIO_170, 170,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_OE, LCD_OE, DBI_B_RDX, AVEIN_DSYNC, GPIO_172, 172,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_PCLK, LCD_PCLK, DBI_B_WRX, AVEIN_VCLK, GPIO_173, 173,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_0, LCD_R_0, DBI_C_RESX, AVEIN_VID16, GPIO_153, 153,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_1, LCD_R_1, DBI_B_D11, AVEIN_VID17, GPIO_152, 152,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_2, LCD_R_2, DBI_B_D12, AVEIN_VID18, GPIO_151, 151,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_3, LCD_R_3, DBI_B_D13, AVEIN_VID19, GPIO_150, 150,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_4, LCD_R_4, DBI_B_D14, AVEIN_VID20, GPIO_149, 149,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_5, LCD_R_5, DBI_B_D15, AVEIN_VID21, GPIO_148, 148,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_6, LCD_R_6, DBI_B_D16, AVEIN_VID22, GPIO_147, 147,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_R_7, LCD_R_7, DBI_B_D17, AVEIN_VID23, GPIO_146, 146,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(LCD_VSYNC, LCD_VSYNC, DBI_B_CSX, AVEIN_VSYNC, GPIO_171, 171,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_VC_2 |
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(MDMGPIO0, GPEN00, RESERVED, RESERVED, GPIO_015, 15,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO1, GPEN01, RESERVED, RESERVED, GPIO_016, 16,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO2, GPEN02, RESERVED, RESERVED, GPIO_017, 17,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO3, GPEN03, RESERVED, RESERVED, GPIO_018, 18,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO4, GPEN04, RESERVED, RESERVED, GPIO_019, 19,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO5, GPEN05, RESERVED, RESERVED, GPIO_020, 20,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO6, GPEN06, RESERVED, RESERVED, GPIO_021, 21,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO7, GPEN07, RESERVED, RESERVED, GPIO_022, 22,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MDMGPIO8, GPEN08, RESERVED, RESERVED, GPIO_023, 23,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_0, MPHI_DATA_0, UARTB5_URXD, SDIO3_DATA_0, GPIO_145,
		 145, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_1, MPHI_DATA_1, UARTB5_UTXD, SDIO3_DATA_1, GPIO_144,
		 144, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_2, MPHI_DATA_2, UARTB5_URTS, SDIO3_DATA_2, GPIO_143,
		 143, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_3, MPHI_DATA_3, UARTB5_UCTS, SDIO3_DATA_3, GPIO_142,
		 142, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_4, MPHI_DATA_4, UARTB6_UTXD, SDIO3_DATA_4, GPIO_141,
		 141, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_5, MPHI_DATA_5, UARTB6_URXD, SDIO3_DATA_5, GPIO_140,
		 140, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_6, MPHI_DATA_6, UARTB6_UCTS, SDIO3_DATA_6, GPIO_139,
		 139, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_7, MPHI_DATA_7, UARTB6_URTS, SDIO3_DATA_7, GPIO_138,
		 138, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_8, MPHI_DATA_8, EAV_GPIO_LTS, CAM1_CAM_DATA5_CPI,
		 GPIO_129, 129, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_9, MPHI_DATA_9, MSTR_CLK_0, CAM1_CAM_HSYNC_CPI,
		 GPIO_123, 123, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_10, MPHI_DATA_10, EAV_SD_0, CAM1_CAM_CLK_CPI,
		 GPIO_121, 121, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_11, MPHI_DATA_11, UARTB2_UCTS, DBI_C_SCL, GPIO_134,
		 134, PIN_DESC_FLAGS_VC_3),
	PIN_DESC(MPHI_DATA_12, MPHI_DATA_12, UARTB2_URTS, CAM1_CAM_DATA9_CPI,
		 GPIO_133, 133, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_13, MPHI_DATA_13, UARTB2_UTXD, CAM1_CAM_DATA8_CPI,
		 GPIO_132, 132, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_14, MPHI_DATA_14, UARTB2_URXD, CAM1_CAM_DATA7_CPI,
		 GPIO_131, 131, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_DATA_15, MPHI_DATA_15, MSTR_CLK_1, CAM1_CAM_DATA6_CPI,
		 GPIO_130, 130, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_HA0, MPHI_HA0, EAV_WS_1, CAM1_CAM_DATA3_CPI, GPIO_127,
		 127, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_HAT0, MPHI_HAT0, EAV_DTE_LTS, CAM1_CAM_DATA4_CPI,
		 GPIO_128, 128, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_HAT1, MPHI_HAT1, VC_GPCLK_0, SDIO3_CLK, GPIO_137, 137,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(MPHI_HCE0_N, MPHI_HCE0_N, EAV_BITCLK_0, CAM1_CAM_DATA0_CPI,
		 GPIO_124, 124, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_HCE1_N, MPHI_HCE1_N, CIR_TX, SDIO3_RST_N, GPIO_136, 136,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_HRD_N, MPHI_HRD_N, EAV_SD_1, CAM1_CAM_DATA2_CPI, GPIO_126,
		 126, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_HWR_N, MPHI_HWR_N, EAV_BITCLK_1, CAM1_CAM_DATA1_CPI,
		 GPIO_125, 125, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_RUN0, MPHI_RUN0, EAV_WS_0, CAM1_CAM_VSYNC_CPI, GPIO_122,
		 122, PIN_DESC_FLAGS_NONE),
	PIN_DESC(MPHI_RUN1, MPHI_RUN1, CIR_RX, SDIO3_CMD, GPIO_135, 135,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(MTX_SCAN_CLK, MTX_SCAN_CLK, AFCPDM, VC_TE1, GPIO_175, 175,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(MTX_SCAN_DATA, MTX_SCAN_DATA, VC_GPIO_7, KP_COL_IP_7, GPIO_174,
		 174, PIN_DESC_FLAGS_VC_2),
	PIN_DESC(NAND_AD_0, NAND_AD_0, SDIO2_DATA_0, AP_RSTN, DEBUG_BUS00, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_1, NAND_AD_1, SDIO2_DATA_1, AP_SCLK_I, DEBUG_BUS01,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_2, NAND_AD_2, SDIO2_DATA_2, AP_LRCK_I, DEBUG_BUS02,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_3, NAND_AD_3, SDIO2_DATA_3, AP_IHF_DATA_I, DEBUG_BUS03,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_4, NAND_AD_4, SDIO2_DATA_4, AP_DAC_DATA_I, DEBUG_BUS04,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_5, NAND_AD_5, SDIO2_DATA_5, EP_AP_EN, DEBUG_BUS05,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_6, NAND_AD_6, SDIO2_DATA_6, DAC_SCL_EN, DEBUG_BUS06,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_AD_7, NAND_AD_7, SDIO2_DATA_7, IHF_AP_EN, DEBUG_BUS07,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_ALE, NAND_ALE, SDIO2_CLK, AP_ADC_DATA_O, DEBUG_BUS10,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_CEN_0, NAND_CEN_0, KP_COL_IP_4, VC_PWM_0, GPIO_045, 45,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(NAND_CEN_1, NAND_CEN_1, USB0PFT, SWDCLKTCK, GPIO_044, 44,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_CLE, NAND_CLE, KP_ROW_OP_5, AP_REF_2P4M_CLK, GPIO_048, 48,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_OEN, NAND_OEN, SDIO2_CMD, HS_AP_EN, DEBUG_BUS09, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_RDY_0, NAND_RDY_0, KP_COL_IP_5, VC_PWM_1, GPIO_046, 46,
		 PIN_DESC_FLAGS_VC_3),
	PIN_DESC(NAND_RDY_1, NAND_RDY_1, USB0PON, SWDIOTMS, GPIO_043, 43,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_WEN, NAND_WEN, SDIO2_RST_N, VIBRA_AP_EN, DEBUG_BUS08,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(NAND_WP, NAND_WP, KP_ROW_OP_4, ADC_AP_EN, GPIO_047, 47,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(PC1, PC1, RESERVED, RESERVED, DEBUG_BUS11, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(PC2, PC2, RESERVED, RESERVED, SPARE_14, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(PMU_INT, PMU_INT, RESERVED, RESERVED, DEBUG_BUS14, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(PMU_SCL, PMU_SCL, RESERVED, RESERVED, SPARE_01, NONE,
		 PIN_DESC_FLAGS_I2C),
	PIN_DESC(PMU_SDA, PMU_SDA, RESERVED, RESERVED, SPARE_02, NONE,
		 PIN_DESC_FLAGS_I2C),
	PIN_DESC(RFST2G_MTSLOTEN3G, RFST2G_MTSLOTEN3G, RESERVED, RESERVED,
		 GPIO_034, 34, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_RX_CTL, RGMII_0_RX_CTL, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_RXC, RGMII_0_RXC, RESERVED, RESERVED, RESERVED, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_RXD_0, RGMII_0_RXD0, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_RXD_1, RGMII_0_RXD1, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_RXD_2, RGMII_0_RXD2, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_RXD_3, RGMII_0_RXD3, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_TX_CTL, RGMII_0_TX_CTL, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_TXC, RGMII_0_TXC, RESERVED, RESERVED, RESERVED, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_TXD_0, RGMII_0_TXD0, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_TXD_1, RGMII_0_TXD1, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_TXD_2, RGMII_0_TXD2, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_0_TXD_3, RGMII_0_TXD3, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_RX_CTL, RGMII_1_RX_CTL, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_RXC, RGMII_1_RXC, RESERVED, RESERVED, RESERVED, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_RXD_0, RGMII_1_RXD0, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_RXD_1, RGMII_1_RXD1, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_RXD_2, RGMII_1_RXD2, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_RXD_3, RGMII_1_RXD3, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_TX_CTL, RGMII_1_TX_CTL, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_TXC, RGMII_1_TXC, RESERVED, RESERVED, RESERVED, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_TXD_0, RGMII_1_TXD0, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_TXD_1, RGMII_1_TXD1, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_TXD_2, RGMII_1_TXD2, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_1_TXD_3, RGMII_1_TXD3, RESERVED, RESERVED, RESERVED,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_GPIO_0, RGMII_GPIO_0, RESERVED, RESERVED, RESERVED, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_GPIO_1, RGMII_GPIO_1, RESERVED, RESERVED, RESERVED, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_GPIO_2, RGMII_GPIO_2, MDIO, RESERVED, SPARE_15, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RGMII_GPIO_3, RGMII_GPIO_3, MDC, RESERVED, SPARE_16, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RTXDATA2G_TXDATA3G1, RTXDATA2G_TXDATA3G1, RESERVED, RESERVED,
		 GPIO_036, 36, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RTXEN2G_TXDATA3G2, RTXEN2G_TXDATA3G2, RESERVED, RESERVED,
		 GPIO_037, 37, PIN_DESC_FLAGS_NONE),
	PIN_DESC(RXDATA3G0, RXDATA3G0, RESERVED, RESERVED, GPIO_038, 38,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RXDATA3G1, RXDATA3G1, RESERVED, RESERVED, GPIO_039, 39,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(RXDATA3G2, RXDATA3G2, RESERVED, RESERVED, GPIO_040, 40,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO1_CLK, SDIO1_CLK, SSP2_CLK, IRD_OSC_11, GPIO_088, 88,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO1_CMD, SDIO1_CMD, SSP2_TXD_0, IRD_OSC_10, GPIO_087, 87,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO1_DATA_0, SDIO1_DATA_0, SSP2_RXD_0, IRD_OSC_9, GPIO_086,
		 86, PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO1_DATA_1, SDIO1_DATA_1, VC_PWM_1, IRD_OSC_8, GPIO_085, 85,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SDIO1_DATA_2, SDIO1_DATA_2, VC_PWM_0, IRD_OSC_7, GPIO_084, 84,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SDIO1_DATA_3, SDIO1_DATA_3, SSP2_FS_0, IRD_OSC_6, GPIO_083, 83,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO4_CLK, SDIO4_CLK, PM_DEBUG0, PTI_CLK, SPIS_CSB, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO4_CMD, SDIO4_CMD, PM_DEBUG1, UARTB2_URXD, SPIS_SCK, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO4_DATA_0, SDIO4_DATA_0, PM_DEBUG2, PTI_DAT0, SPIS_MISO,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO4_DATA_1, SDIO4_DATA_1, PM_DEBUG3, PTI_DAT1, SPIS_MOSI,
		 NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO4_DATA_2, SDIO4_DATA_2, SWDIOTMS, PTI_DAT2, GPIO_090, 90,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SDIO4_DATA_3, SDIO4_DATA_3, SWDCLKTCK, PTI_DAT3, GPIO_089, 89,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM_CLK, SIM_CLK, UARTB5_URTS, IRD_OSC_3, GPIO_050, 50,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM_DATA, SIM_DATA, UARTB5_UCTS, IRD_OSC_4, GPIO_051, 51,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM_DET, SIM_DET, CLKMON, IRD_OSC_5, GPIO_052, 52,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM_RESETN, SIM_RESETN, RESERVED, IRD_OSC_2, GPIO_049, 49,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM2_CLK, SIM2_CLK, UARTB5_UTXD, KP_ROW_OP_6, GPIO_054, 54,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM2_DATA, SIM2_DATA, UARTB5_URXD, KP_COL_IP_7, GPIO_055, 55,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SIM2_DET, SIM2_DET, VC_PWM_1, KP_ROW_OP_7, GPIO_056, 56,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SIM2_RESETN, SIM2_RESETN, USB1PON, KP_COL_IP_6, GPIO_053, 53,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SRI_C, SRI_C, RESERVED, RESERVED, GPIO_031, 31,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SRI_D, SRI_D, RESERVED, RESERVED, GPIO_033, 33,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SRI_E, SRI_E, RESERVED, RESERVED, GPIO_032, 32,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP_EXTCLK, SSP_EXTCLK, VC_CPG1, DBI_C_SCL, GPIO_108, 108,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(SSP0_CLK, SSP0_CLK, UARTB5_UCTS, RFGPO_2, GPIO_092, 92,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP0_FS, SSP0_FS, UARTB5_URTS, RFGPO_3, GPIO_091, 91,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP0_RXD, SSP0_RXD, UARTB5_URXD, RFGPO_1, GPIO_093, 93,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP0_TXD, SSP0_TXD, UARTB5_UTXD, RFGPO_0, GPIO_094, 94,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_CLK, SSP2_CLK, KP_COL_IP_2, WCDMA_DEBUG_4, GPIO_099, 99,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_FS_0, SSP2_FS_0, KP_ROW_OP_2, WCDMA_DEBUG_0, GPIO_095, 95,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_FS_1, SSP2_FS_1, KP_ROW_OP_3, WCDMA_DEBUG_1, GPIO_096, 96,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_FS_2, SSP2_FS_2, KP_ROW_OP_4, WCDMA_DEBUG_2, GPIO_097, 97,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_FS_3, SSP2_FS_3, KP_ROW_OP_5, WCDMA_DEBUG_3, GPIO_098, 98,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_RXD_0, SSP2_RXD_0, KP_COL_IP_3, WCDMA_DEBUG_5, GPIO_100,
		 100, PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_RXD_1, SSP2_RXD_1, KP_COL_IP_4, WCDMA_DEBUG_7, GPIO_102,
		 102, PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP2_TXD_0, SSP2_TXD_0, VC_GPIO_6, WCDMA_DEBUG_6, GPIO_101,
		 101, PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP2_TXD_1, SSP2_TXD_1, KP_COL_IP_5, RFGPO_5, GPIO_103, 103,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP3_CLK, SSP3_CLK, VC_I2S_SCK, DBI_C_CSX, GPIO_105, 105,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(SSP3_FS, SSP3_FS, VC_I2S_WSIO, DBI_C_RESX, GPIO_104, 104,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(SSP3_RXD, SSP3_RXD, VC_I2S_SDI, DBI_C_DIN, GPIO_106, 106,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(SSP3_TXD, SSP3_TXD, VC_I2S_SDO, DBI_C_DOUT, GPIO_107, 107,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(SSP4_CLK, SSP4_CLK, VC_TCK, ACFLAG, GPIO_110, 110,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP4_FS, SSP4_FS, VC_TMS, ACDATA, GPIO_109, 109,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP4_RXD, SSP4_RXD, VC_TDI, ACREADY, GPIO_111, 111,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP4_TXD, SSP4_TXD, VC_TDO, ACWAKE, GPIO_112, 112,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP5_CLK, SSP5_CLK, RTCK, CAFLAG, GPIO_114, 114,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP5_FS, SSP5_FS, VC_TRSTB, CADATA, GPIO_113, 113,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP5_RXD, SSP5_RXD, VC_GPIO_7, CAREADY, GPIO_115, 115,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP5_TXD, SSP5_TXD, DBI_C_RESX, CAWAKE, GPIO_116, 116,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(SSP6_CLK, SSP6_CLK, UARTB4_UTXD, PM_DEBUG1, GPIO_118, 118,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP6_FS, SSP6_FS, UARTB4_URXD, PM_DEBUG0, GPIO_117, 117,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP6_RXD, SSP6_RXD, UARTB4_URTS, PM_DEBUG2, GPIO_119, 119,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SSP6_TXD, SSP6_TXD, UARTB4_UCTS, PM_DEBUG3, GPIO_120, 120,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(STAT_1, STAT_1, SIM_LDO_EN, PC3, DEBUG_BUS13, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(STAT_2, STAT_2, SIM2_LDO_EN, RESERVED, DEBUG_BUS12, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(SYSCLKEN, SYSCLKEN, RESERVED, RESERVED, GPIO_042, 42,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACECLK, TRACECLK, PTI_CLK, MDM_DSP_TRACE_CLK, SPARE_00, NONE,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT00, TRACEDT00, PTI_DAT0, MDM_DSP_TRACE_DAT00,
		 DEBUG_BUS00, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT01, TRACEDT01, PTI_DAT1, MDM_DSP_TRACE_DAT01,
		 DEBUG_BUS01, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT02, TRACEDT02, PTI_DAT2, MDM_DSP_TRACE_DAT02,
		 DEBUG_BUS02, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT03, TRACEDT03, PTI_DAT3, MDM_DSP_TRACE_DAT03,
		 DEBUG_BUS03, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT04, TRACEDT04, PM_DEBUG3, MDM_DSP_TRACE_DAT04,
		 DEBUG_BUS04, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT05, TRACEDT05, PM_DEBUG2, MDM_DSP_TRACE_DAT05,
		 DEBUG_BUS05, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT06, TRACEDT06, PM_DEBUG1, MDM_DSP_TRACE_DAT06,
		 DEBUG_BUS06, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT07, TRACEDT07, PM_DEBUG0, MDM_DSP_TRACE_DAT07,
		 DEBUG_BUS07, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT08, TRACEDT08, RESERVED, MDM_DSP_TRACE_DAT08,
		 DEBUG_BUS08, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT09, TRACEDT09, RESERVED, MDM_DSP_TRACE_DAT09,
		 DEBUG_BUS09, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT10, TRACEDT10, RESERVED, MDM_DSP_TRACE_DAT10,
		 DEBUG_BUS10, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT11, TRACEDT11, RESERVED, MDM_DSP_TRACE_DAT11,
		 DEBUG_BUS11, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT12, TRACEDT12, RESERVED, MDM_DSP_TRACE_DAT12,
		 DEBUG_BUS12, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT13, TRACEDT13, RESERVED, MDM_DSP_TRACE_DAT13,
		 DEBUG_BUS13, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT14, TRACEDT14, RESERVED, MDM_DSP_TRACE_DAT14,
		 DEBUG_BUS14, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TRACEDT15, TRACEDT15, UARTB2_URXD, MDM_DSP_TRACE_DAT15,
		 DEBUG_BUS15, NONE, PIN_DESC_FLAGS_NONE),
	PIN_DESC(TXDATA3G0, TXDATA3G0, RESERVED, RESERVED, GPIO_035, 35,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(TXPWRIND, GPEN11, RESERVED, RESERVED, GPIO_026, 26,
		 PIN_DESC_FLAGS_NONE),
	PIN_DESC(UARTB1_UCTS, UARTB1_UCTS, VC_TE2, KP_COL_IP_6, PC3, NONE,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(UARTB1_URTS, UARTB1_URTS, VC_TE1, THERMAL_SHUTDOWN, GPIO_071,
		 71, PIN_DESC_FLAGS_VC_2),
	PIN_DESC(UARTB1_URXD, UARTB1_URXD, VC_GPIO_4, KP_ROW_OP_6, GPIO_069, 69,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(UARTB1_UTXD, UARTB1_UTXD, VC_TE0, KP_ROW_OP_7, GPIO_070, 70,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(UARTB2_URXD, UARTB2_URXD, VC_TRSTB, WCDMA_UART_RXD, GPIO_073,
		 73, PIN_DESC_FLAGS_VC_2),
	PIN_DESC(UARTB2_UTXD, UARTB2_UTXD, RTCK, WCDMA_UART_TXD, GPIO_074, 74,
		 PIN_DESC_FLAGS_VC_2),
	PIN_DESC(UARTB3_UCTS, UARTB3_UCTS, KP_COL_IP_6, WCDMA_CLK2, GPIO_076,
		 76, PIN_DESC_FLAGS_NONE),
	PIN_DESC(UARTB3_URTS, UARTB3_URTS, KP_ROW_OP_6, WCDMA_CLK1, GPIO_075,
		 75, PIN_DESC_FLAGS_NONE),
	PIN_DESC(UARTB3_URXD, UARTB3_URXD, KP_COL_IP_7, WCDMA_SYNC, GPIO_077,
		 77, PIN_DESC_FLAGS_NONE),
	PIN_DESC(UARTB3_UTXD, UARTB3_UTXD, KP_ROW_OP_7, WCDMA_CLK3, GPIO_078,
		 78, PIN_DESC_FLAGS_NONE),
	PIN_DESC(UARTB4_UCTS, UARTB4_UCTS, VC_TCK, DBI_C_DIN, GPIO_080, 80,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(UARTB4_URTS, UARTB4_URTS, VC_TMS, DBI_C_CSX, GPIO_079, 79,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(UARTB4_URXD, UARTB4_URXD, VC_TDI, DBI_C_DOUT, GPIO_081, 81,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(UARTB4_UTXD, UARTB4_UTXD, VC_TDO, DBI_C_SCL, GPIO_082, 82,
		 PIN_DESC_FLAGS_VC_2 | PIN_DESC_FLAGS_VC_3),
	PIN_DESC(VC_CAM1_SCL, VC_CAM1_SCL, BSC3_SCL, RESERVED, SPARE_03, NONE,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_I2C),
	PIN_DESC(VC_CAM1_SDA, VC_CAM1_SDA, BSC3_SDA, RESERVED, SPARE_04, NONE,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_I2C),
	PIN_DESC(VC_CAM2_SCL, VC_CAM2_SCL, BSC3_SCL, RESERVED, GPIO_065, 65,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_I2C),
	PIN_DESC(VC_CAM2_SDA, VC_CAM2_SDA, BSC3_SDA, RESERVED, GPIO_066, 66,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_I2C),
	PIN_DESC(VC_CAM3_SCL, VC_CAM3_SCL, BSC3_SCL, RESERVED, GPIO_067, 67,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_I2C),
	PIN_DESC(VC_CAM3_SDA, VC_CAM3_SDA, BSC3_SDA, RESERVED, GPIO_068, 68,
		 PIN_DESC_FLAGS_VC_1 | PIN_DESC_FLAGS_I2C),
};

struct chip_pin_desc g_chip_pin_desc = {
	.desc_tbl = pin_desc_tbl,
};

int __init pinmux_chip_init(void)
{
	g_chip_pin_desc.base = ioremap(PAD_CTRL_BASE_ADDR, SZ_2K);
	BUG_ON(!g_chip_pin_desc.base);

	return 0;
}