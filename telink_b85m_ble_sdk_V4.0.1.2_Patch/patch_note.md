## V4.0.1.2_Patch_0001

### Bug Fixes
* When MTU>23, data crosstalk happens occassionally if several connections' L2CAP packets consist of start fragment and continuation fragments. A connection's continuation fragment may reassemble to another connection's start fragment.

### BREAKING CHANGES
  - N/A


### Bug Fixes
* 当MTU>23时，l2cap packet如果由start fragment和continuation fragment组成，底层拼包有概率出现continuation fragment和不属于自己的start fragment组成一个l2cap包的情况，即产生串扰。

### BREAKING CHANGES
  - N/A