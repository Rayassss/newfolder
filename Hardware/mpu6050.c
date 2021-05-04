/*
 * mpu6050.c
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 *
 *  Contact information
 *  -------------------
 *
 * e-mail   :  leech001@gmail.com
 */

/*
 * |---------------------------------------------------------------------------------
 * | Copyright (C) Bulanov Konstantin,2019
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |
 * | Kalman filter algorithm used from https://github.com/TKJElectronics/KalmanFilter
 * |---------------------------------------------------------------------------------
 */


#include <math.h>
#include "mpu6050.h"
#include "uart.h"

#define RAD_TO_DEG 57.295779513082320876798154814105

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

// Setup MPU6050
#define MPU6050_ADDR 0x68
const uint16_t i2c_timeout = 100;
const double Accel_Z_corrector = 14418.0;

uint32_t timer;

Kalman_t KalmanX = {
    .Q_angle = 0.001f,
    .Q_bias = 0.003f,
    .R_measure = 0.03f
};

Kalman_t KalmanY = {
    .Q_angle = 0.001f,
    .Q_bias = 0.003f,
    .R_measure = 0.03f,
};
//
//uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx) {
//    uint8_t check;
//    uint8_t Data;
//    HAL_Delay(1000);
//    // check device ID WHO_AM_I
//    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);
//    if (check == 113)  // 0x68 will be returned by the sensor if everything goes well
//    {
//        // power management register 0X6B we should write all 0's to wake the sensor up
//        Data = 0;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);
//
//        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
//        Data = 0x07;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);
//
//        // Set accelerometer configuration in ACCEL_CONFIG Register
//        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
//        Data = 0x00;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);
//
//        // Set Gyroscopic configuration in GYRO_CONFIG Register
//        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
//        Data = 0x00;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);
//        return 0;
//    }
//    return 1;
//}
void MPU6050_WriteReg(u8 reg_add, u8 reg_dat) {
    i2c_Start();
    i2c_SendByte(MPU6050_SLAVE_ADDRESS);
    i2c_WaitAck();
    i2c_SendByte(reg_add);
    i2c_WaitAck();
    i2c_SendByte(reg_dat);
    i2c_WaitAck();
    i2c_Stop();
}

/**
  * @brief   ´ÓMPU6050¼Ä´æÆ÷¶ÁÈ¡Êý¾Ý
  * @param
  * @retval
  */
void MPU6050_ReadData(u8 reg_add, unsigned char *Read, u8 num) {
    unsigned char i;

    i2c_Start();
    i2c_SendByte(MPU6050_SLAVE_ADDRESS);
    i2c_WaitAck();
    i2c_SendByte(reg_add);
    i2c_WaitAck();

    i2c_Start();
    i2c_SendByte(MPU6050_SLAVE_ADDRESS + 1);
    i2c_WaitAck();

    for (i = 0; i < (num - 1); i++) {
        *Read = i2c_ReadByte(1);
        Read++;
    }
    *Read = i2c_ReadByte(0);
    i2c_Stop();
}

/**
  * @brief   ³õÊ¼»¯MPU6050Ð¾Æ¬
  * @param
  * @retval
  */
void MPU6050_Init(void) {
    int i = 0, j = 0;
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 1000; j++) { ;
        }
    }
    MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);        //½â³ýÐÝÃß×´Ì¬
    MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV, 0x07);        //ÍÓÂÝÒÇ²ÉÑùÂÊ£¬1KHz
    MPU6050_WriteReg(MPU6050_RA_CONFIG, 0x06);            //µÍÍ¨ÂË²¨Æ÷µÄÉèÖÃ£¬½ØÖ¹ÆµÂÊÊÇ1K£¬´ø¿íÊÇ5K
    MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG, 0x00);      //ÅäÖÃ¼ÓËÙ¶È´«¸ÐÆ÷¹¤×÷ÔÚ2GÄ£Ê½£¬²»×Ô¼ì
    MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //ÍÓÂÝÒÇ×Ô¼ì¼°²âÁ¿·¶Î§£¬µäÐÍÖµ£º0x18(²»×Ô¼ì£¬2000deg/s)
}

/**
  * @brief   ¶ÁÈ¡MPU6050µÄID
  * @param
  * @retval
  */
uint8_t MPU6050ReadID(void) {
    unsigned char Re = 0;
    MPU6050_ReadData(MPU6050_RA_WHO_AM_I, &Re, 1);    //¶ÁÆ÷¼þµØÖ·
    if (Re != 0x68) {
        print_usart1("MPU6050 dectected error!\r\n");
        return 0;
    } else {
        print_usart1("MPU6050 ID = %d\r\n", Re);
        return 1;
    }

}
/**
  * @brief   ¶ÁÈ¡MPU6050µÄ¼ÓËÙ¶ÈÊý¾Ý
  * @param
  * @retval
  */
void MPU6050ReadAcc(short *accData) {
    u8 buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

/**
  * @brief   ¶ÁÈ¡MPU6050µÄ½Ç¼ÓËÙ¶ÈÊý¾Ý
  * @param
  * @retval
  */
void MPU6050ReadGyro(short *gyroData) {
    u8 buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT, buf, 6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}
void MPU6050_Read_Accel(MPU6050_t *DataStruct) {
    short Rec_Data[6];
    MPU6050ReadAcc(Rec_Data);
    // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    DataStruct->Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into acceleration in 'g'
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 16384.0
         for more details check ACCEL_CONFIG Register              ****/

    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
}

void MPU6050_Read_Gyro(MPU6050_t *DataStruct) {
    short Rec_Data[6];
    MPU6050ReadGyro(Rec_Data);
    // Read 6 BYTES of data starting from GYRO_XOUT_H register


    DataStruct->Gyro_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Gyro_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Gyro_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;
}
void MPU6050_Read_All(MPU6050_t *DataStruct) {
    short acc_data[6];
    short gyro_data[6];
    MPU6050ReadAcc(acc_data);
    MPU6050ReadGyro(gyro_data);
    // Read 14 BYTES of data starting from ACCEL_XOUT_H register

    DataStruct->Accel_X_RAW = (int16_t) (acc_data[0] << 8 | acc_data[1]);
    DataStruct->Accel_Y_RAW = (int16_t) (acc_data[2] << 8 | acc_data[3]);
    DataStruct->Accel_Z_RAW = (int16_t) (acc_data[4] << 8 | acc_data[5]);
    DataStruct->Gyro_X_RAW = (int16_t) (gyro_data[0] << 8 | gyro_data[1]);
    DataStruct->Gyro_Y_RAW = (int16_t) (gyro_data[2] << 8 | gyro_data[3]);
    DataStruct->Gyro_Z_RAW = (int16_t) (gyro_data[4] << 8 | gyro_data[5]);

    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;

    // Kalman angle solve
    double dt = 1000;
    double roll;
    double roll_sqrt = sqrt(
        DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
    if (roll_sqrt != 0.0) {
        roll = atan(DataStruct->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
    } else {
        roll = 0.0;
    }
    double pitch = atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW) * RAD_TO_DEG;
    if ((pitch < -90 && DataStruct->KalmanAngleY > 90) || (pitch > 90 && DataStruct->KalmanAngleY < -90)) {
        KalmanY.angle = pitch;
        DataStruct->KalmanAngleY = pitch;
    } else {
        DataStruct->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
    }
    if (fabs(DataStruct->KalmanAngleY) > 90)
        DataStruct->Gx = -DataStruct->Gx;
    DataStruct->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, DataStruct->Gy, dt);

}

double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt) {
    double rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    double S = Kalman->P[0][0] + Kalman->R_measure;
    double K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    double y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    double P00_temp = Kalman->P[0][0];
    double P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
};

