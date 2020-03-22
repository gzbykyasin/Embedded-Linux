/****************************
****MUX CONTROL REGISTERS****
*****************************/
#define IOMUXC_GPIO5                                    0x2290000
#define IOMUXC_GPIO1                                    0x20E0000

/************************
*****GPIO1 REGISTERS*****
*************************/
#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00                0x20E005C 
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00                0x20E02E8

#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01                0x20E0060
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01                0x20E02EC

#define D0_MUX                                          IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00
#define D0_PAD                                          IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00

#define D1_MUX                                          IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01
#define D1_PAD                                          IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01

/************************
*****GPIO5 REGISTERS*****
*************************/
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER0         0x2290008
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER0         0x229004C

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1         0x229000C
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER1         0x2290050

#define D0_MUX                                          IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER0
#define D0_PAD                                          IOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER0

#define D1_MUX                                          IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER1
#define D1_PAD                                          IOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER1