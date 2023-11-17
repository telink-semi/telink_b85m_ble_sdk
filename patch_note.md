## V4.0.1.3_Patch_0001

### Bug Fixes
Fix an issue:Very few chips, low probability of insufficient vibration of 24M crystal after sleep wake-up, resulting in a crash
Fix an issue:Secure Connection level 3, deep retention is enabled, and the pairing fails with a low probability.
Fix an issue:In Extended Scan mode, the adv packet using Code PHY cannot be received from the primary channel.
Fix an issue:In Extended Scan mode, the RSSI value in the Extended ADV report event is incorrect.
Fix an issue:In Extended Scan mode, when a connection is created as the Central, the receive window may be too small to receive AUX_CONNECT_RSP packets. This causes the created connection to fail.

### BREAKING CHANGES
  - N/A


### Bug Fixes
* 修复:极少数芯片，低概率出现睡眠唤醒后24M晶体起振不充分，导致死机
* 修复:Secure Connection level 3，低功耗开启deep retention，低概率配对失败。
* 修复:在Extended Scan mode，无法收到primary channel使用Code PHY的广播包。
* 修复:在Extended Scan mode，Extended ADV report event中RSSI值异常。
* 修复:在Extended Scan mode，作为master创建连接，由于接收窗口太小导致有概率出现无法接收AUX_CONNECT_RSP数据包的情况。这样就导致创建连接失败。

### BREAKING CHANGES
  - N/A