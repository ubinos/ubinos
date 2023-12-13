/*
 * Copyright (c) 2022 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UBIDRV_UART_IO_H_
#define UBIDRV_UART_IO_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @file uart.h
 *
 * @brief UART IO API
 *
 * UART 장치를 사용한 IO API를 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>
#include <ubinos/ubidrv/uart.h>

/*!
 * UART 장치에서 데이터를 읽는 함수 (전부 읽을 때까지 기다림)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @param   buffer              읽은 데이터를 저장할 버퍼의 주소
 *
 * @param   length              읽을 크기
 *
 * @param   read                읽은 크기
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_read(int fd, uint8_t *buffer, uint32_t length, uint32_t *read);

/*!
 * UART 장치에서 데이터를 읽는 함수 (최대 주어진 시간 만큼 기다름)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @param   buffer              읽은 데이터를 저장할 버퍼의 주소
 *
 * @param   length              읽을 크기
 *
 * @param   read                읽은 크기
 *
 * @param   timeoutms           기다릴 최대 시간
 *
 * @param   remain_timeoutms    (기다릴 최대 시간 - 기다린 시간) 값을 돌려줄 변수의 포인터
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_read_timedms(int fd, uint8_t *buffer, uint32_t length, uint32_t *read, uint32_t timeoutms, uint32_t *remain_timeoutms);

/*!
 * UART 장치에 데이터를 쓰는 함수 (전부 쓸때까지 기다림)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @param   buffer              쓸 데이터가 저장된 버퍼의 주소
 *
 * @param   length              쓸 크기
 *
 * @param   written             쓰여진 크기
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_write(int fd, uint8_t *buffer, uint32_t length, uint32_t *written);

/*!
 * UART 장치에서 데이터를 쓰는 함수 (최대 주어진 시간 만큼 기다름)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @param   buffer              쓸 데이터가 저장된 버퍼의 주소
 *
 * @param   length              쓸 크기
 *
 * @param   read                쓰여진 크기
 *
 * @param   timeoutms           기다릴 최대 시간
 *
 * @param   remain_timeoutms    (기다릴 최대 시간 - 기다린 시간) 값을 돌려줄 변수의 포인터
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_write_timedms(int fd, uint8_t *buffer, uint32_t length, uint32_t *written, uint32_t timeoutms, uint32_t *remain_timeoutms);

/*!
 * UART 장치의 읽기 버퍼를 비우는 함수 (비워질 때까지 기다림)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_read_buf_clear(int fd);

/*!
 * UART 장치의 읽기 버퍼를 비우는 함수 (최대 주어진 시간 만큼 기다름)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @param   timeoutms           기다릴 최대 시간
 *
 * @param   remain_timeoutms    (기다릴 최대 시간 - 기다린 시간) 값을 돌려줄 변수의 포인터
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_read_buf_clear_timedms(int fd, uint32_t timeoutms, uint32_t *remain_timeoutms);

/*!
 * UART 장치의 쓰기 버퍼에 저장된 데이터 출력을 완료하는 함수 (완료될 때까지 기다림)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_flush(int fd);

/*!
 * UART 장치의 쓰기 버퍼에 저장된 데이터 출력을 완료하는 함수 (최대 주어진 시간 만큼 기다름)
 *
 * @param   fd                  대상 장치 파일 디스크립터
 *
 * @param   timeoutms           기다릴 최대 시간
 *
 * @param   remain_timeoutms    (기다릴 최대 시간 - 기다린 시간) 값을 돌려줄 변수의 포인터
 *
 * @return  상태 번호
 */
ubi_st_t ubidrv_uart_io_flush_timedms(int fd, uint32_t timeoutms, uint32_t *remain_timeoutms);

#ifdef __cplusplus
}
#endif

#endif /* UBIDRV_UART_IO_H_ */
