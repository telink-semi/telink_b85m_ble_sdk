/********************************************************************************************************
 * @file	usb_desc.h
 *
 * @brief	This is the header file for BLE SDK
 *
 * @author	BLE GROUP
 * @date	2020.06
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *          
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *          
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *          
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions 
 *              in binary form must reproduce the above copyright notice, this list of 
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *          
 *              3. Neither the name of TELINK, nor the names of its contributors may be 
 *              used to endorse or promote products derived from this software without 
 *              specific prior written permission.
 *          
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or 
 *              relating to such deletion(s), modification(s) or alteration(s).
 *         
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *         
 *******************************************************************************************************/
#pragma once

#include <application/usbstd/CDCClassCommon.h>

enum {
	BTUSB_USB_STRING_LANGUAGE = 0,
	BTUSB_USB_STRING_VENDOR,
	BTUSB_USB_STRING_PRODUCT,
	BTUSB_USB_STRING_SERIAL,
};

typedef struct {
	USB_Descriptor_Configuration_Hdr_t Config;
	USB_Descriptor_Interface_Association_t intfa;

	USB_Descriptor_Interface_t intf0;
	USB_Descriptor_Endpoint_t irq_in;
	USB_Descriptor_Endpoint_t bulk_in;
	USB_Descriptor_Endpoint_t bulk_out;

	USB_Descriptor_Interface_t intf1_0;
	USB_Descriptor_Endpoint_t iso_in;
	USB_Descriptor_Endpoint_t iso_out;

	USB_Descriptor_Interface_t intf1_1;
	USB_Descriptor_Endpoint_t iso_in1;
	USB_Descriptor_Endpoint_t iso_out1;

	USB_Descriptor_Interface_t intf_prn;
	USB_Descriptor_Endpoint_t endp0;
	USB_Descriptor_Endpoint_t endp1;
} BTUSB_Descriptor_Configuration_with_Printer_t;

typedef struct {
	USB_Descriptor_Configuration_Hdr_t Config;
	USB_Descriptor_Interface_Association_t intfa;

	USB_Descriptor_Interface_t intf0;
	USB_Descriptor_Endpoint_t irq_in;
	USB_Descriptor_Endpoint_t bulk_in;
	USB_Descriptor_Endpoint_t bulk_out;

	USB_Descriptor_Interface_t intf1_0;
	USB_Descriptor_Endpoint_t iso_in;
	USB_Descriptor_Endpoint_t iso_out;

	USB_Descriptor_Interface_t intf1_1;
	USB_Descriptor_Endpoint_t iso_in1;
	USB_Descriptor_Endpoint_t iso_out1;
} BTUSB_Descriptor_Configuration_t;

/**
 * @brief	This function is used to obtain USB language descriptor
 * @param	none
 * @return	the address of language_desc struct
 */
u8* btusb_usbdesc_get_language(void);

/**
 * @brief	This function is used to obtain USB vendor descriptor
 * @param	none
 * @return	the address of vendor_desc struct
 */
u8* btusb_usbdesc_get_vendor(void);

/**
 * @brief	This function is used to obtain USB product descriptor
 * @param	none
 * @return	the address of product_desc struct
 */
u8* btusb_usbdesc_get_product(void);

/**
 * @brief	This function is used to obtain USB serial descriptor
 * @param	none
 * @return	the address of serial_desc struct
 */
u8* btusb_usbdesc_get_serial(void);

/**
 * @brief	This function is used to obtain USB device descriptor
 * @param	none
 * @return	the address of device_desc struct
 */
u8* btusb_usbdesc_get_device(void);

/**
 * @brief	This function is used to obtain USB configuration descriptor
 * @param	none
 * @return	the address of configuration_desc_cdc or configuration_desc struct
 */
u8* btusb_usbdesc_get_configuration(void);

/**
 * @brief	This function is used to obtain the size of USB configuration descriptor
 * @param	none
 * @return	the size of configuration_desc_cdc or configuration_desc struct
 */
int btusb_usbdesc_get_configuration_size(void);

/**
 * @brief	This function is used to set CDC device enable
 * @param	en- enable CDC device
 * @return	none.
 */
void btusb_select_cdc_device (int en);

///////////////////////////////////////////////////////////////////////////////

#define CMD_GET_VERSION                 0 //0x00
#define CMD_SELECT_DPIMPL               16//0x10
#define CMD_SET_TCK_FREQUENCY           17//0x11
#define CMD_GET_TCK_FREQUENCY           18//0x12
#define CMD_MEASURE_MAX_TCK_FREQ        21//0x15
#define CMD_MEASURE_RTCK_RESPONSE       22//0x16
#define CMD_TAP_SHIFT                   23//0x17
#define CMD_SET_TAPHW_STATE             32//0x20
#define CMD_GET_TAPHW_STATE             33//0x21
#define CMD_TGPWR_SETUP                 34//0x22



//---------------  CDC ----------------------------------

/** Endpoint number of the CDC device-to-host notification IN endpoint. */
#define CDC_NOTIFICATION_EPNUM         2
/** Endpoint number of the CDC device-to-host data IN endpoint. */
#define CDC_TX_EPNUM                   4
/** Endpoint number of the CDC host-to-device data OUT endpoint. */
#define CDC_RX_EPNUM                   5
/** Size in bytes of the CDC device-to-host notification IN endpoint. */
#define CDC_NOTIFICATION_EPSIZE        8
/** Size in bytes of the CDC data IN and OUT endpoints. */
#define CDC_TXRX_EPSIZE                64

enum {
    USB_STRING_LANGUAGE = 0,
    USB_STRING_VENDOR,
    USB_STRING_PRODUCT,
    USB_STRING_SERIAL,
};

// interface id
typedef enum {
    USB_INTF_CDC_CCI,
    USB_INTF_CDC_DCI,
    USB_INTF_MAX,
} USB_INTF_ID_E;

typedef struct {
    // CDC Control Interface
    USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
    USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
    USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
    USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_CallManagement;
    USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

    // CDC Data Interface
    USB_Descriptor_Interface_t               CDC_DCI_Interface;
    USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
    USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
} USB_CDC_Descriptor_t;

typedef struct {
    USB_Descriptor_Configuration_Hdr_t Config;
    USB_Descriptor_Interface_Association_t cdc_iad;
    USB_Descriptor_Interface_t cdc_interface;
    USB_CDC_Descriptor_t cdc_descriptor;
} USB_Descriptor_Configuration_t;
