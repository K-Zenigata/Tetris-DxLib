cmake_minimum_required(VERSION 3.0.0)
project(Tetris_DxLib VERSION 0.1.0)

# 生成する実行ファイルの名前を指定
set( OUTPUT main )

# ソースファイルのリストを自動的に取得
file(GLOB SOURCES "source/*.cpp")

# ヘッダーファイルのリストを自動的に取得
file(GLOB HEADERS "include/*.hpp")

# DxLibが置かれているディレクトリを指定
set( DX_INC_DIR 自身の環境のインクルードパス/include/DxLib/ )
set( DX_LIB_DIR 自身の環境のリブパス/lib/DxLib/ )

# 実行可能ファイルのビルド
add_executable(${OUTPUT} ${SOURCES} ${HEADERS})

target_include_directories( ${OUTPUT} PUBLIC ${DX_INC_DIR} )

target_link_directories( ${OUTPUT} PUBLIC ${DX_LIB_DIR} )

# コンパイルフラグに-DDX_GCC_COMPILEを付けてなければならないことに注意
target_compile_options( ${OUTPUT} PUBLIC
  -Wall
  -DDX_GCC_COMPILE )

# C++標準規格の指定( cxx_std_20はcmake3.12以降で指定可能 )
target_compile_features( ${OUTPUT} PUBLIC cxx_std_20 )

# リンクするライブラリの指定
# 公式サイトによると、この順番で指定しなければ、正しくリンクされないことがあるらしい
set( DXLIB_LIBRARY_LIST DxLib;DxUseCLib;DxDrawFunc;jpeg;png;zlib;tiff;theora_static;vorbis_static;vorbisfile_static;ogg_static;bulletdynamics;bulletcollision;bulletmath;opusfile;opus;silk_common;celt;-static;-lstdc++ )

target_link_libraries( ${OUTPUT} PUBLIC ${DXLIB_LIBRARY_LIST} )
