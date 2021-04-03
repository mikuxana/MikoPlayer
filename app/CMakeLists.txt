cmake_minimum_required(VERSION 3.4.1)


# 定义一个变量
file(GLOB source_file src/main/cpp/*.cpp)

add_library(

        native-lib
        SHARED
        ${source_file}

        )


include_directories(src/main/cpp/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}")


target_link_libraries(
                       native-lib
        # 静态注意引入顺序
        # android 内存映射异常 修改minSdkVersion 为21
                avformat avcodec avfilter avutil  swresample swscale
        # ffmpeg依赖libz.so
                        z
                       log)