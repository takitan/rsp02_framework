/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "rsp02_framework", "index.html", [
    [ "BOOTプロセス", "md_doc_boot.html", [
      [ "ブート", "md_doc_boot.html#autotoc_md1", null ],
      [ "main()", "md_doc_boot.html#autotoc_md2", [
        [ "Initalize()", "md_doc_boot.html#autotoc_md3", [
          [ "　LogSystem.Initialize()", "md_doc_boot.html#autotoc_md4", null ],
          [ "DBCCommandRoot.Initialize()", "md_doc_boot.html#autotoc_md5", null ],
          [ "CommandRootlInitialize()", "md_doc_boot.html#autotoc_md6", null ],
          [ "StateRoot.Initialize()", "md_doc_boot.html#autotoc_md7", null ],
          [ "ProcessRoot.Initialize()", "md_doc_boot.html#autotoc_md8", null ]
        ] ],
        [ "MainLoop()", "md_doc_boot.html#autotoc_md9", null ]
      ] ]
    ] ],
    [ "fsm(Finite State Machine)", "md_fw_fsm_doc_fsm.html", [
      [ "はじめに", "md_fw_fsm_doc_fsm.html#autotoc_md11", null ],
      [ "モデル", "md_fw_fsm_doc_fsm.html#autotoc_md12", null ],
      [ "クラス図", "md_fw_fsm_doc_fsm.html#autotoc_md13", [
        [ "IState", "md_fw_fsm_doc_fsm.html#autotoc_md14", null ],
        [ "StateBase", "md_fw_fsm_doc_fsm.html#autotoc_md15", null ],
        [ "StateFactory", "md_fw_fsm_doc_fsm.html#autotoc_md16", null ],
        [ "StateInfo", "md_fw_fsm_doc_fsm.html#autotoc_md17", null ],
        [ "TinyEvent", "md_fw_fsm_doc_fsm.html#autotoc_md18", [
          [ "メソッド", "md_fw_fsm_doc_fsm.html#autotoc_md19", [
            [ "void Set(size_t n)", "md_fw_fsm_doc_fsm.html#autotoc_md20", null ],
            [ "void Reset(size_t n)", "md_fw_fsm_doc_fsm.html#autotoc_md21", null ],
            [ "bool TestAndReset(size_t n)", "md_fw_fsm_doc_fsm.html#autotoc_md22", null ],
            [ "bool Test(size_t n)", "md_fw_fsm_doc_fsm.html#autotoc_md23", null ]
          ] ]
        ] ]
      ] ]
    ] ],
    [ "FSMの実装方法", "md_fw_fsm_doc_fsm_implement.html", [
      [ "はじめに", "md_fw_fsm_doc_fsm_implement.html#autotoc_md25", null ],
      [ "状態の記述方法", "md_fw_fsm_doc_fsm_implement.html#autotoc_md26", null ]
    ] ],
    [ "logger(ログシステム)", "md_fw_logger_doc_logger.html", [
      [ "はじめに", "md_fw_logger_doc_logger.html#autotoc_md28", [
        [ "背景", "md_fw_logger_doc_logger.html#autotoc_md29", null ],
        [ "目的", "md_fw_logger_doc_logger.html#autotoc_md30", null ],
        [ "アーキテクチャ", "md_fw_logger_doc_logger.html#autotoc_md31", [
          [ "クラス図", "md_fw_logger_doc_logger.html#autotoc_md32", null ]
        ] ],
        [ "ILogger", "md_fw_logger_doc_logger.html#autotoc_md33", [
          [ "API", "md_fw_logger_doc_logger.html#autotoc_md34", [
            [ "void Log( ELogLevel ll, const char* fmt, ::va_list arg)", "md_fw_logger_doc_logger.html#autotoc_md35", null ],
            [ "void Log( ELogLevel ll, const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md36", null ],
            [ "void Trace(const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md37", null ],
            [ "void Debug(const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md38", null ],
            [ "void Info(const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md39", null ],
            [ "void Warn(const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md40", null ],
            [ "void Error(const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md41", null ],
            [ "void Fatal(const char* fmt, ...)", "md_fw_logger_doc_logger.html#autotoc_md42", null ],
            [ "void SetLogLevel( ELogLevel lv)", "md_fw_logger_doc_logger.html#autotoc_md43", null ],
            [ "bool SetLogLevel( const char* lv)", "md_fw_logger_doc_logger.html#autotoc_md44", null ],
            [ "const char* Name() const", "md_fw_logger_doc_logger.html#autotoc_md45", null ]
          ] ]
        ] ]
      ] ]
    ] ],
    [ "sink", "md_fw_logger_doc_sink.html", [
      [ "はじめに", "md_fw_logger_doc_sink.html#autotoc_md47", [
        [ "目的", "md_fw_logger_doc_sink.html#autotoc_md48", null ],
        [ "初期実装で提供するsink", "md_fw_logger_doc_sink.html#autotoc_md49", [
          [ "FifoSink", "md_fw_logger_doc_sink.html#autotoc_md50", null ],
          [ "FileSink", "md_fw_logger_doc_sink.html#autotoc_md51", null ],
          [ "NullSink", "md_fw_logger_doc_sink.html#autotoc_md52", null ],
          [ "PrintfSink", "md_fw_logger_doc_sink.html#autotoc_md53", null ]
        ] ]
      ] ]
    ] ],
    [ "Process", "md_middle_con_pro_doc_Process.html", [
      [ "はじめに", "md_middle_con_pro_doc_Process.html#autotoc_md55", null ],
      [ "アーキテクチャ", "md_middle_con_pro_doc_Process.html#autotoc_md56", [
        [ "プロセスモデル", "md_middle_con_pro_doc_Process.html#autotoc_md57", null ],
        [ "プロセス連鎖", "md_middle_con_pro_doc_Process.html#autotoc_md58", [
          [ "縦続(Series)", "md_middle_con_pro_doc_Process.html#autotoc_md59", null ],
          [ "結合(Join)", "md_middle_con_pro_doc_Process.html#autotoc_md60", null ],
          [ "分岐(Fork)", "md_middle_con_pro_doc_Process.html#autotoc_md61", null ]
        ] ],
        [ "クラス図", "md_middle_con_pro_doc_Process.html#autotoc_md62", [
          [ "IProcess", "md_middle_con_pro_doc_Process.html#autotoc_md63", null ],
          [ "IExecuter", "md_middle_con_pro_doc_Process.html#autotoc_md64", null ],
          [ "IConsumer", "md_middle_con_pro_doc_Process.html#autotoc_md65", null ],
          [ "Producer", "md_middle_con_pro_doc_Process.html#autotoc_md66", null ]
        ] ],
        [ "プロセスモデル", "md_middle_con_pro_doc_Process.html#autotoc_md67", [
          [ "プロセスの種類", "md_middle_con_pro_doc_Process.html#autotoc_md68", null ]
        ] ],
        [ "プロセスの実装", "md_middle_con_pro_doc_Process.html#autotoc_md69", null ],
        [ "プロセス実装の実際", "md_middle_con_pro_doc_Process.html#autotoc_md70", [
          [ "プロセスの登録", "md_middle_con_pro_doc_Process.html#autotoc_md71", null ]
        ] ]
      ] ]
    ] ],
    [ "RSP02-Framework", "md_README.html", [
      [ "これはなに？", "md_README.html#autotoc_md109", [
        [ "コマンド解釈", "md_README.html#autotoc_md110", null ],
        [ "状態遷移", "md_README.html#autotoc_md111", null ],
        [ "ログシステム", "md_README.html#autotoc_md112", null ],
        [ "時間取得機構", "md_README.html#autotoc_md113", null ]
      ] ],
      [ "実装方針", "md_README.html#autotoc_md114", null ],
      [ "ディレクトリ構造", "md_README.html#autotoc_md115", [
        [ "実装が必要なソースコード", "md_README.html#autotoc_md116", [
          [ "TLV_library/rsp02_*.hpp", "md_README.html#autotoc_md117", [
            [ "定義詳細", "md_README.html#autotoc_md118", null ]
          ] ],
          [ "GlobalDefine.hpp", "md_README.html#autotoc_md119", [
            [ "定義詳細", "md_README.html#autotoc_md120", null ]
          ] ],
          [ "LogSystem.cpp", "md_README.html#autotoc_md121", null ],
          [ "main.cpp", "md_README.html#autotoc_md122", null ],
          [ "states/StateRoot.hpp , StateRoot.cpp", "md_README.html#autotoc_md123", null ],
          [ "processes/ProcessRoot.hpp , ProcessRoot.cpp", "md_README.html#autotoc_md124", null ],
          [ "debug_command/DBGCommandRoot.hpp , DBGCommandRoot.cpp", "md_README.html#autotoc_md125", null ],
          [ "command/CommandRoot.hpp , CommandRoot.cpp", "md_README.html#autotoc_md126", null ]
        ] ]
      ] ],
      [ "クラス図", "md_README.html#autotoc_md127", null ]
    ] ],
    [ "LogSystem", "md_src_LogSystem.html", [
      [ "API", "md_src_LogSystem.html#autotoc_md129", [
        [ "Initialize", "md_src_LogSystem.html#autotoc_md130", null ]
      ] ],
      [ "外部参照", "md_src_LogSystem.html#autotoc_md131", [
        [ "extern TLogSYstem LogSystem", "md_src_LogSystem.html#autotoc_md132", null ]
      ] ],
      [ "logger", "md_src_LogSystem.html#autotoc_md133", null ]
    ] ],
    [ "CommandKernel", "md_src_processes_doc_CommandKernel.html", null ],
    [ "MessageConverter Process", "md_src_processes_doc_MessageConverter.html", [
      [ "動作", "md_src_processes_doc_MessageConverter.html#autotoc_md136", null ]
    ] ],
    [ "ProcessRoot", "md_src_processes_doc_ProcessRoot.html", [
      [ "API", "md_src_processes_doc_ProcessRoot.html#autotoc_md138", [
        [ "コンストラクタ", "md_src_processes_doc_ProcessRoot.html#autotoc_md139", null ],
        [ "Initialize", "md_src_processes_doc_ProcessRoot.html#autotoc_md140", null ]
      ] ]
    ] ],
    [ "StateMachine", "md_src_processes_doc_StateMachine.html", [
      [ "動作", "md_src_processes_doc_StateMachine.html#autotoc_md142", null ]
    ] ],
    [ "TLVDatalinkUp,TLVDatalinkDown", "md_src_processes_doc_TLVDatalink.html", [
      [ "動作", "md_src_processes_doc_TLVDatalink.html#autotoc_md144", null ]
    ] ],
    [ "TLVStub", "md_src_processes_doc_TLVStub.html", null ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "Modules", "modules.html", "modules" ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", null ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Related Functions", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", null ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"CommandImplBase_8hpp.html",
"classTDBGCommandRoot.html#abd3efb6a48900a7a23db8b56b2f2f0f2",
"classrsp_1_1rsp02_1_1fw_1_1util_1_1Callback_3_01R_07ArgTs_8_8_8_08_4.html#ae5107157ae4fc006349354ca2bcde18f",
"globals_vars.html",
"ntlibc_8h.html#a9bf3b201f5cf98afce6e75bd28c7fd4f",
"structTLVpacket__t.html#a22ad20e8326196319f5da4795616141b",
"tlv_2rsp02__cdh_8hpp.html#a74408d5942234e1ab964ccbec05975a6af2ce16945de0f76c11ab7ae1faba85be"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';