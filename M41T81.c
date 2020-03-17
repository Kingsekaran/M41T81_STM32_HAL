#include "gpio.h"
#include "M41T81.h"
#include "stm32f1xx_hal.h"
#include"stdio.h"
#include "i2c.h"

uint8_t bcdToDec(uint8_t bcd) {
	return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

uint8_t decToBCD(uint8_t dec) {
	return ((dec / 10) << 4) + (dec % 10);
}

uint8_t read_register(uint8_t addr) {
	uint8_t data[8];
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, addr, 1, data, 1, 100);
	return data[0];
}
void RTC_init() {
	uint8_t value[8];
	sprintf(value, "%c", 0x3F);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x0C, 1, value, 1, 100);
}
uint8_t get_seconds() {
	uint8_t sec = read_register(0x01);
	return bcdToDec(sec & 0x7F);
}
uint8_t get_minits() {
	uint8_t min = read_register(0x02);
	return bcdToDec(min & 0x7F);
}
uint8_t get_hours() {
	uint8_t hour = read_register(0x03);
	return bcdToDec(hour & 0x3F);
}
uint8_t get_Date() {
	uint8_t date = read_register(0x05);
	return bcdToDec(date & 0x3F);
}
uint8_t get_Month() {
	uint8_t month = read_register(0x06);
	return bcdToDec(month & 0x1F);
}
uint8_t get_Year() {
	uint8_t year = read_register(0x07);
	return bcdToDec(year);
}
void set_seconds(unsigned short int sec) {
	uint8_t value[8];
	uint8_t yert = decToBCD(sec);
	sprintf(value, "%c", yert);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x01, 1, value, 1, 100);
}
void set_minits(unsigned short int min) {
	uint8_t value[8];
	uint8_t yert = decToBCD(min);
	sprintf(value, "%c", yert);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x02, 1, value, 1, 100);
}
void set_hours(unsigned short int hour) {
	uint8_t value[8];
	uint8_t yert = decToBCD(hour);
	sprintf(value, "%c", yert);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x03, 1, value, 1, 100);
}
void set_Date(unsigned short int date) {
	uint8_t value[8];
	uint8_t yert = decToBCD(date);
	sprintf(value, "%c", yert);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x05, 1, value, 1, 100);

}
void set_Month(unsigned short int month) {
	uint8_t value[8];
	uint8_t yert = decToBCD(month & 0x1F);
	sprintf(value, "%c", yert);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x06, 1, value, 1, 100);
}
void set_year(unsigned short int year) {
	uint8_t value[8];
	uint8_t yert = decToBCD(year);
	sprintf(value, "%c", yert);
	HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x07, 1, value, 1, 100);
}

