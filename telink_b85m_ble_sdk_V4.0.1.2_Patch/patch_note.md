## V4.0.1.2_Patch_0003

### Features
* Support 8238.

### Bug Fixes
* Fixed disconnection when there is long user task in main loop.
* Fixed connection failure when jumping over first packet after master's Connect Ind.
* Fixed "MIC Fail" disconnection due to AES reentrancy.
* Release blc_ll_register_user_irq_handler_cb() API to solve the data loss problem of hardware interfaces (eg. UART) in Adv status.
* Fixed that Slave will still send the Security Request, thought SMP is disabled. 

### BREAKING CHANGES
  - N/A

 ### Features
* 支持8238。


### Bug Fixes
* 修复mainloop用户任务长时间阻塞，导致连接断开。
* 修复Slave在收到Connect Ind之后没有收到第一个包的情况下产生断连。
* 修复AES重入导致的 MIC Fail 断连。
* 释放blc_ll_register_user_irq_handler_cb api接口，解决在广播态下存在的硬件接口（如UART等）数据丢失问题。
* 修复SMP关闭的情况下，Slave仍然会发送Security Request。

### BREAKING CHANGES
  - N/A

## V4.0.1.2_Patch_0002

### Features
* Add API blc_ll_checkBleTaskIsIdle() to get BLE task idle status.
* Optimize Adv validation timing after disabled and enabled Adv.
* Add API blc_ll_continue_adv_after_scan_req() to set continuing advertising on other channels after receiving scan request.
* Add API blc_ll_register_user_irq_handler_cb() to solve the problem of hardware interface (eg. UART) data miss under Adv status.


### Bug Fixes
* Fix abnormal phenomenon when there is no stack task in some cases.
* Fix the problem of disconnection after receiving Connection Indication/Connection Update in some cases.


### BREAKING CHANGES
  - N/A


 ### Features
* 增加blc_ll_checkBleTaskIsIdle api接口，获取底层蓝牙任务是否处于Idle状态。
* 优化enable或disable广播生效时间。
* 增加blc_ll_continue_adv_after_scan_req api接口，用于设置在收到Scan Req之后，继续在其他通道进行广播。
* 增加blc_ll_register_user_irq_handler_cb api接口，解决在广播态下存在的硬件接口（如UART等）数据丢失问题。


### Bug Fixes
* 修复修复协议栈没有任务时程序可能运行异常的Bug。
* 修复在create Connection /connection parameter update时候可能出现收不到包的现象，导致断连问题。


### BREAKING CHANGES
  - N/A


## V4.0.1.2_Patch_0001

### Bug Fixes
* When MTU>23, data crosstalk happens occassionally if several connections' L2CAP packets consist of start fragment and continuation fragments. A connection's continuation fragment may reassemble to another connection's start fragment.

### BREAKING CHANGES
  - N/A


### Bug Fixes
* 当MTU>23时，l2cap packet如果由start fragment和continuation fragment组成，底层拼包有概率出现continuation fragment和不属于自己的start fragment组成一个l2cap包的情况，即产生串扰。

### BREAKING CHANGES
  - N/A