## V4.0.1.2

### Notes
* Customers must confirm flash size in app_config.h

### Features
* SDK version：telink_b85m_ble_sdk_V4.0.1.2
* This version sdk support 8253/8258/8273/8278 chip.
* Optimize the process of channel map/phy/connection parameter update.
* Clean application code to make user feel better to use, such as using MACRO to calulate related buffer size automatically.
* Add some APIs according to users' feedback.
  +  Long sleep API.
  +  RSSI get API.
  +  OTA max timeout prolonged to 1000s from 250s.

### Bug Fixes
  +  Connection parameter update abnormally under PM.
  +  Inaccurate T_IFS in CONNECT_IND, SCAN_RSP, AUX_CONNECT_REQ.
  +  Long run time of software timer callback affects timing logic.

### BREAKING CHANGES
  - N/A



### Notes
* 用户必须要在app_config.h中确认flash size与当前所用芯片相符。

### Features
* SDK 版本：telink_b85m_ble_sdk_V4.0.1.2
* 支持8253/8258/8273/8278。
* 优化Channel map/PHY/Connection parameter更新流程。
* 清理优化应用层代码，提高用户友好性，比如用宏自动计算相关的buffer大小。
* 根据用户反馈，增加了如下API。
  +  长休眠。
  +  获取RSSI。
  +  OTA超时设置上限从250s调整到1000s。

### Bug Fixes
  +  连接参数在PM下更新异常。
  +  CONNECT_IND, SCAN_RSP, AUX_CONNECT_REQ的T_IFS时间不准。
  +  软件定时器回调运行太长影响时序逻辑错误。

### BREAKING CHANGES
  - N/A






## V4.0.1.1-Beta

### Features
* SDK version：telink_b85m_ble_sdk_V4.0.1.1-Beta
* This version sdk support 8253/8258/8273/8278 chip.
* Release relevant m4s4.a/m1s1.a/m0s4.a that cost different ram size.
* Support maximum 4 master and 4 slave connections simultaneous.
* Support low power management(b85m_slave and b85m_m1s1 support deepsleep retention mode).
* Support Extended Advertising/Extended Scan/Periodic Advertising/Periodic Scan.
* Support core version 5.0.
* Demo illustration.
  +  4 master and 4 slave demo: b85m_demo
  +  1 master and 1 slave demo: b85m_m1s1
  +  master demo: b85m_master_dongle
  +  slave demo: b85m_slave
  +  controller demo: b85m_controller
  +  feature demo: b85m_feature

### BREAKING CHANGES
  - N/A



### Features
* SDK 版本：telink_b85m_ble_sdk_V4.0.1.1-Beta
* 支持8253/8258/8273/8278。
* 提供m4s4.a/m1s1.a/m0s4.a，不同的库消耗的ram大小不同。
* 支持最多4个master和4个slave同时连接。
* 支持低功耗管理（b85m_slave和b85m_m1s1支持deepsleep retention mode）。
* 支持扩展广播、扩展扫描、周期性广播及扫描。
* 支持core 5.0版本。
* Demo 描述.
  +  4 master and 4 slave demo: b85m_demo
  +  1 master and 1 slave demo: b85m_m1s1
  +  master demo: b85m_master_dongle
  +  slave demo: b85m_slave
  +  controller demo: b85m_controller
  +  feature demo: b85m_feature

### BREAKING CHANGES
  - N/A






## V4.0.0

### Features
* SDK version: telink_b85m_ble_sdk_alpha_v4.0.0.
* This version sdk support 825x/827x chip.
* Support connect slave(maximum 4) and master(maximum 4) simultaneously without low power manage.
* Support 1M/2M/Coded PHY.
* Support Extended Advertising.
* Support CSA#2.
* HCI(controller) Support H4 and H5(3-wire) two transmission protocols. 
* Demo illustration.
  +  master and slave demo:b85m_demo 
  +  controller demo:b85m_controller
  +  feature demo：b85m_feature
  +  only master demo：b85m_master_dongle 

### BREAKING CHANGES
* N/A



### Features
* SDK 版本：telink_b85m_ble_sdk_alpha_v4.0.0。
* 该版本支持825x、827x两种芯片。
* 同时支持4个master和4个slave连接。
* 支持1M/2M/Coded PHY。
* 支持扩展广播。
* 支持跳频算法2。
* controller支持H4/H5（3-wire）两种传输协议。
* Demo illustration.
  +  master and slave demo: b85m_demo 
  +  controller demo: b85m_controller
  +  feature demo：b85m_feature
  +  only master demo：b85m_master_dongle 

### BREAKING CHANGES
* N/A
