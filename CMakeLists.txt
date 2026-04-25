cmake_minimum_required(VERSION 3.16)
project(FSR_homeworks)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)  # GNU99
set(CMAKE_C_FLAGS "-Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign")
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_SOURCE_DIR}/*.c"
)
add_executable(FSR_homeworks ${SRC_FILES}
        semester2/yandex/2026-02-16/A.c
        semester1/yandex/2025-12-15/B.c
        "semester2/informatics/2026-03-12_1_shortest_paths/A.c"
        "semester2/informatics/2026-03-12_1_shortest_paths/B.c"
        semester2/yandex/2026-02-16/B.c
        semester2/yandex/2026-02-26/A.c
        semester2/yandex/2026-03-02/A.c
        "semester2/informatics/2026-03-12_1_shortest_paths/C.c"
        "semester2/informatics/2026-03-12_1_shortest_paths/D.c"
        "semester2/informatics/2026-03-12_2_streams/A.c"
        "semester2/informatics/2026-03-12_2_streams/B.c"
        "semester2/informatics/2026-03-12_1_shortest_paths/E.c"
        "semester2/informatics/2026-04-19_1_elementary geometry/A.c"
        "semester2/informatics/2026-04-19_1_elementary geometry/B.c"
        "semester2/informatics/2026-04-19_1_elementary geometry/C.c"
        "semester2/informatics/2026-04-19_1_elementary geometry/D.c"
        "semester2/informatics/2026-04-19_1_elementary geometry/E.c"
        semester2/yandex/2026-03-23/A_Jarvis.c
        semester2/yandex/2026-03-23/B.c
        "semester2/informatics/2026-04-19_2_convex_hull/A.c"
        semester2/yandex/2026-03-26/A_Bentley_Ottmann.c
        "semester2/informatics/2026-04-19_2_convex_hull/B.c"
        "semester2/informatics/2026-04-19_2_convex_hull/C.c"
        semester2/informatics/2026-04-19_2_convex_hull/D.c
        semester2/informatics/2026-04-19_2_convex_hull/E.c
        semester2/informatics/2026-04-19_2_convex_hull/F.c
        semester2/informatics/2026-04-19_3_sweeping_line/D.c
        semester2/informatics/2026-04-19_3_sweeping_line/B.c
        semester2/informatics/2026-04-19_2_convex_hull/G.c
)
