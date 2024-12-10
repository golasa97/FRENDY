add_library(CommonUtils
    CommentRemover.cpp
    DigitAdjuster.cpp
    ErrorManager.cpp
    FileCommentRemover.cpp
    StringUtils.cpp
    TabAdjuster.cpp
    TimeUtils.cpp
    VectorClearer.cpp
    VectorCopier.cpp
    VectorSizeChecker.cpp
    TabInterpolator.cpp
)

target_include_directories(CommonUtils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(CommonUtils PUBLIC Config)
