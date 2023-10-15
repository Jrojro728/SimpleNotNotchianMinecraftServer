#pragma once
#include "pch.h"

//�������
binlog::TextOutputStream static out(std::cout, "[%d] [%C/%S] [%M]: %m\n", "%H:%M:%S.%N");

//������־�����
#define BINLOG_TRACE_CONSUME(...) BINLOG_TRACE(__VA_ARGS__); binlog::consume(out);
#define BINLOG_DEBUG_CONSUME(...) BINLOG_DEBUG(__VA_ARGS__); binlog::consume(out);
#define BINLOG_INFO_CONSUME(...) BINLOG_INFO(__VA_ARGS__); binlog::consume(out);
#define BINLOG_WARN_CONSUME(...) BINLOG_WARN(__VA_ARGS__); binlog::consume(out);
#define BINLOG_ERROR_CONSUME(...) BINLOG_ERROR(__VA_ARGS__); binlog::consume(out);
#define BINLOG_CRITICAL_CONSUME(...) BINLOG_CRITICAL(__VA_ARGS__); binlog::consume(out);

//������־(�Զ��幤��)�����
#define BINLOG_TRACE_W_CONSUME(worker, ...) BINLOG_TRACE_W(worker, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_DEBUG_W_CONSUME(worker, ...) BINLOG_DEBUG_W(worker, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_INFO_W_CONSUME(worker, ...) BINLOG_INFO_W(worker, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_WARN_W_CONSUME(worker, ...) BINLOG_WARN_W(worker, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_CRITICAL_W_CONSUME(worker, ...) BINLOG_CRITICAL_W(worker, __VA_ARGS__); worker.session().consume(out);

//������־�����(�Զ������)
#define BINLOG_TRACE_C_CONSUME(category, ...) BINLOG_TRACE_C(category, __VA_ARGS__); binlog::consume(out);
#define BINLOG_DEBUG_C_CONSUME(category, ...) BINLOG_DEBUG_C(category, __VA_ARGS__); binlog::consume(out);
#define BINLOG_INFO_C_CONSUME(category, ...) BINLOG_INFO_C(category, __VA_ARGS__); binlog::consume(out);
#define BINLOG_WARN_C_CONSUME(category, ...) BINLOG_WARN_C(category, __VA_ARGS__); binlog::consume(out);
#define BINLOG_ERROR_C_CONSUME(category, ...) BINLOG_ERROR_C(category, __VA_ARGS__); binlog::consume(out);
#define BINLOG_CRITICAL_C_CONSUME(category, ...) BINLOG_CRITICAL_C(category, __VA_ARGS__); binlog::consume(out);

//������־(�Զ��幤��,���)�����
#define BINLOG_TRACE_WC_CONSUME(worker, category, ...) BINLOG_TRACE_WC(worker, category, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_DEBUG_WC_CONSUME(worker, category, ...) BINLOG_DEBUG_WC(worker, category, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_INFO_WC_CONSUME(worker, category, ...) BINLOG_INFO_WC(worker, category, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_WARN_WC_CONSUME(worker, category, ...) BINLOG_WARN_WC(worker, category, __VA_ARGS__); worker.session().consume(out);
#define BINLOG_CRITICAL_WC_CONSUME(worker, category, ...) BINLOG_CRITICAL_WC(worker, category, __VA_ARGS__); worker.session().consume(out);