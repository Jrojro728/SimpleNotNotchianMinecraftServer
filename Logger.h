#pragma once

#include <iostream>

#include <binlog/binlog.hpp>
#include <binlog/TextOutputStream.hpp>

//文字输出
binlog::TextOutputStream static out(std::cout, "[%d] [%C/%S] [%M]: %m (%G:%L) \n", "%H:%M:%S");

//创建日志并输出
#define BINLOG_TRACE_CONSUME(...) BINLOG_TRACE(__VA_ARGS__); binlog::consume(out);
#define BINLOG_DEBUG_CONSUME(...) BINLOG_DEBUG(__VA_ARGS__); binlog::consume(out);
#define BINLOG_INFO_CONSUME(...) BINLOG_INFO(__VA_ARGS__); binlog::consume(out);
#define BINLOG_WARN_CONSUME(...) BINLOG_WARN(__VA_ARGS__); binlog::consume(out);
#define BINLOG_ERROR_CONSUME(...) BINLOG_ERROR(__VA_ARGS__); binlog::consume(out);
#define BINLOG_CRITICAL_CONSUME(...) BINLOG_CRITICAL(__VA_ARGS__); binlog::consume(out);

//创建日志(自定义工人)并输出
#define BINLOG_TRACE_W_CONSUME(worker, ...) BINLOG_TRACE_W(worker, __VA_ARGS__); binlog::consume(out);
#define BINLOG_DEBUG_W_CONSUME(worker, ...) BINLOG_DEBUG_W(worker, __VA_ARGS__); binlog::consume(out);
#define BINLOG_INFO_W_CONSUME(worker, ...) BINLOG_INFO_W(worker, __VA_ARGS__); binlog::consume(out);
#define BINLOG_WARN_W_CONSUME(worker, ...) BINLOG_WARN_W(worker, __VA_ARGS__); binlog::consume(out);
#define BINLOG_CRITICAL_W_CONSUME(worker, ...) BINLOG_CRITICAL_W(worker, __VA_ARGS__); binlog::consume(out);

#define BINLOG_TRACE_CONSUME_S(s, ...) BINLOG_TRACE_W(binlog::SessionWriter(s), __VA_ARGS__); s.consume(out);
#define BINLOG_DEBUG_CONSUME_S(s, ...) BINLOG_DEBUG(__VA_ARGS__); s.consume(out);
#define BINLOG_INFO_CONSUME_S(s, ...) BINLOG_INFO(__VA_ARGS__); s.consume(out);
#define BINLOG_WARN_CONSUME_S(s, ...) BINLOG_WARN(__VA_ARGS__); s.consume(out);
#define BINLOG_ERROR_CONSUME_S(s, ...) BINLOG_ERROR(__VA_ARGS__); s.consume(out);
#define BINLOG_CRITICAL_CONSUME_S(s, ...) BINLOG_CRITICAL(__VA_ARGS__); s.consume(out);