#pragma once
#include "stdint.h"

#pragma pack(push, 1)  
    struct DAQParameter
    {
        int     frame_num_in_callback; // 一次回调帧数
        int     OpticalPort;//DAQ 设备启用状态  bit[0-3]对应设备0-3 启用状态 1:启用，0:禁用 
        int     ADC_fs;             // 采样率
        int     DownSampleM;             // 降采样系数
        int     sample_num;         // 采样点数

        int     sensor_num;         // 通道数
        unsigned short trigger_mode; // 触发模式
        unsigned short trigger_fs;  // 触发频率
        unsigned short trigger_delay; // 触发延迟
        unsigned short voltageA;     //发射电压A
        unsigned short voltageB;     //发射电压B
        unsigned short voltageC;     //发射电压C
        unsigned short voltageD;     //发射电压D
        unsigned short voltageE;     //发射电压E
        unsigned short voltageF;     //发射电压F
        unsigned int FilterLPByPass; // 低通滤波Bypass: 0 启用，1 禁用
        unsigned int FilterLPShiftBit; // 带通滤波移位位数
        unsigned int FilterBPByPass; // 带通滤波Bypass: 0 启用，1 禁用
        unsigned int FilterBPShiftBit; // 带通滤波移位位数

        unsigned int ECG_SAMPLE_EN ;//ECG 数据采集开关
        unsigned int Encoder_Scan_En ;//编码器数据采集开关
    };
#pragma pack(pop)
    /******************************控制命令******************************/
    // 1.创建 SDK
    /// </summary>
    /// <param name="isSave">是否实时存储标志。1:ture,other:false</param>
    /// <param name="directoryName">存储目录</param>
    /// <returns></returns>		
    void open_SDK(int isSave, const char* directoryName);
    // 2.向FPGA 下发扫查指令 (tips:配置扫查参数步骤顺序任意，但必须在setDAQ之前，且不能在扫查期间) <returns>0,成功;-1,软件未建立连接;-2,驱动状态异常;-3,设备连接状态异常</returns>
    int setDAQ(struct DAQParameter param);
    // 3.开始扫查 
    int start_sample();
    // 4.切换数据存储状态 参数定义同open_SDK,在扫查中关闭或开启数据存储
    int SetIsSave(int isSave, const char* directoryName);
    // 5.扫查中获取单帧数据  <returns>-1:数据为空,other:数据起始帧号</returns>		
    int getOneFrameData(int8_t** data);
    // 6.停止扫查  
    int stop_sample();
    // 7.关闭 SDK 
    int close_SDK();
    /******************************配置扫查参数******************************/
    //配置AFE 寄存器默认值
     /// </summary>
    /// <param name="addr">寄存器地址</param>
    /// <param name="val">寄存器值</param>
    /// <returns></returns>		
    void set_afe_reg(int addr, int val);
    // 配置 Tx08D 寄存器
    /// </summary>
    /// <param name="addr">寄存器地址</param>
    /// <param name="val">寄存器值</param>
    /// <returns></returns>		
    void set_tx_registers(uint32_t addr, uint32_t val);
    //配置 Tx08D 发射序列
    /// </summary>
    /// <param name="tx_index">发射序列号</param>
    /// <param name="inner_index">序列内寄存器组号</param>
    /// <param name="addr">寄存器地址</param>
    /// <param name="val">寄存器值</param>
    /// <returns></returns>		
    void set_tx_arg(int tx_index, int inner_index, uint32_t addr, uint32_t val);
    // 配置 TVG 序列
    /// </summary>
    /// <param name="tvg_val_us">采样衰减参数(超声)</param>
    /// <param name="tvg_val_pact">采样衰减参数(光声)</param>
    /// <param name="tvg_attenuation_time">衰减参数时间</param>
    /// <returns></returns>		
    void set_tvg_arg(int tvg_val_us, int tvg_val_pact, int tvg_attenuation_time);
    // 配置 PRT 序列 
    /// </summary>
    /// <param name="scanlenth">发射序列号</param>
    /// <param name="triggerdelay">触发延迟</param>
    /// <param name="scantime">采样时长</param>
    /// <param name="repeatNum">重复次数</param>
    /// <returns></returns>		
    void set_prt_arg(int mode_type,int scanlenth, uint32_t triggerdelay, uint32_t scantime, uint32_t repeatNum);
   // 配置 设备同步同步触发脉宽 序列
    /// </summary>
    /// <param name="index">下标范围0-4</param>
    /// <param name="value">脉宽(ns)</param>
    /// <returns></returns>		
    void set_sync_pulse_width_arg(uint8_t index, uint8_t value);
    // 配置 设备同步同步触发延迟 序列 
    /// </summary>
    /// <param name="index">下标范围0-4</param>
    /// <param name="value">延迟(ns)</param>
    /// <returns></returns>		
    void set_sync_trigger_delay_arg(uint8_t index, uint16_t value);
    // 配置 设备同步状态标志位 
    /// </summary>
    /// <param name="mux">bit[0]-bit[4]对应5个探头状态</param>
    /// <param name="bank">0对应超声，1对应光声</param>
    /// <returns></returns>		
    void set_sync_status(uint8_t mux, uint8_t bank);
    // 配置 扫描数据头
    /// </summary>
    /// <param name="sln">线号</param>
    /// <param name="mode_type">模式类型</param>
    /// <param name="frame_end">帧结束标志</param>
    /// <param name="frame_start">帧起始标志</param>
    /// <param name="scan_len">采样长度</param>
    /// <param name="other">参考示例</param>
    /// <returns></returns>		
    void set_scanHead(int frame, int sln, int mode_type, int pack_size, int beam, int pulse_type, int frame_end, int frame_start, int scan_len);
    // 配置 AFE 解调参数
    /// </summary>模式配置
    /// <param name="mode_num">总模式数</param>
    /// <param name="mode_id">当前模式号</param>
    /// <param name="profile_id">Profile</param>
    /// <param name="line_num">总线数</param>
    /// <param name="line_start_id">结束线号</param>
    /// <returns></returns>		
    void set_afe_mode(int mode_num, int mode_id, int profile_id, int line_num, int line_start_id);
    /// </summary>AFE profile配置
    /// <param name="profile_num">总行数</param>
    /// <param name="profile_id">行序号</param>
    /// <param name="val[]">参数</param>
    /// <param name="vallen">参数长度</param>
    /// <returns></returns>		
    void set_afe_profile(int profile_num, int profile_id, int val[], int vallen);
    /// </summary>AFE 滤波系数配置
    /// <param name="filter_num">滤波器参数总行数</param>
    /// <param name="filter_id">滤波器参数行序号</param>
    /// <param name="val0-val7">滤波器参数1-7</param>
    /// <returns></returns>		
    void set_afe_filter(int filter_num, int filter_id, int val0, int val1, int val2, int val3, int val4, int val5, int val6, int val7);
    /// </summary>低通滤波系数配置
    /// <param name="index">低通滤波系数号,0 - 31</param> 0 - 31
    /// <param name="value">低通滤波系数值</param> 
    /// <returns></returns>		
    void set_LPCoef(int index, uint32_t value);
    /// </summary>带通滤波系数配置
    /// <param name="index">带通滤波系数号,0 - 31</param>
    /// <param name="value">带通滤波器参数总行数</param>
    /// <returns></returns>		
    void set_BPCoef(int index, uint32_t value);
    // 配置 设备使能状态标志位 
    /// </summary>
    /// <param name="CMUT_BIAS">用于控制CMUT_BIAS使能/param>
    /// <param name="P_D3V3_EN">用于控制 探头电源使能</param>
    /// <param name="P_PRE_EN">用于控制 前置放大器电源使能</param>
    /// <returns></returns>		
    void set_device_en(uint8_t CMUT_BIAS, uint8_t P_D3V3_EN, uint8_t P_PRE_EN);



