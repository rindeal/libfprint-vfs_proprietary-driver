/*******************************************************************************
 * Copyright 2018  Jan Chren (rindeal)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef UNION_OF_STRUCT_N_ARRAY_H_
#define UNION_OF_STRUCT_N_ARRAY_H_


#include "pp_narg.h"


#define UNION_OF_STRUCT_N_FOR_EACH_1(type, name) \
        type name;
#define UNION_OF_STRUCT_N_FOR_EACH_2(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_1(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_3(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_2(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_4(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_3(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_5(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_4(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_6(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_5(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_7(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_6(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_8(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_7(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_9(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_8(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_10(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_9(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_11(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_10(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_12(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_11(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_13(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_12(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_14(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_13(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_15(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_14(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_16(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_15(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_17(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_16(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_18(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_17(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_19(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_18(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_20(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_19(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_21(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_20(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_22(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_21(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_23(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_22(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_24(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_23(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_25(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_24(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_26(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_25(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_27(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_26(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_28(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_27(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_29(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_28(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_30(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_29(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_31(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_30(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_32(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_31(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_33(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_32(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_34(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_33(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_35(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_34(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_36(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_35(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_37(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_36(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_38(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_37(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_39(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_38(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_40(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_39(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_41(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_40(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_42(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_41(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_43(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_42(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_44(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_43(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_45(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_44(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_46(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_45(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_47(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_46(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_48(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_47(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_49(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_48(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_50(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_49(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_51(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_50(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_52(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_51(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_53(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_52(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_54(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_53(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_55(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_54(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_56(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_55(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_57(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_56(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_58(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_57(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_59(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_58(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_60(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_59(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_61(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_60(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_62(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_61(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_63(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_62(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_64(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_63(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_65(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_64(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_66(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_65(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_67(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_66(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_68(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_67(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_69(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_68(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_70(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_69(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_71(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_70(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_72(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_71(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_73(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_72(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_74(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_73(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_75(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_74(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_76(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_75(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_77(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_76(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_78(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_77(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_79(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_78(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_80(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_79(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_81(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_80(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_82(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_81(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_83(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_82(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_84(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_83(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_85(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_84(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_86(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_85(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_87(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_86(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_88(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_87(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_89(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_88(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_90(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_89(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_91(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_90(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_92(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_91(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_93(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_92(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_94(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_93(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_95(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_94(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_96(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_95(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_97(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_96(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_98(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_97(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_99(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_98(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_100(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_99(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_101(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_100(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_102(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_101(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_103(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_102(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_104(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_103(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_105(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_104(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_106(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_105(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_107(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_106(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_108(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_107(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_109(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_108(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_110(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_109(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_111(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_110(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_112(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_111(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_113(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_112(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_114(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_113(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_115(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_114(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_116(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_115(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_117(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_116(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_118(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_117(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_119(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_118(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_120(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_119(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_121(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_120(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_122(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_121(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_123(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_122(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_124(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_123(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_125(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_124(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_126(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_125(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_127(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_126(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_128(type, name, ...) \
        type name; \
        UNION_OF_STRUCT_N_FOR_EACH_127(type, __VA_ARGS__)

#define UNION_OF_STRUCT_N_ARRAY_PASTE3_(x, y)  x ## y
#define UNION_OF_STRUCT_N_ARRAY_PASTE2_(x, y)  UNION_OF_STRUCT_N_ARRAY_PASTE3_(x, y)
#define UNION_OF_STRUCT_N_ARRAY_PASTE(x, y)    UNION_OF_STRUCT_N_ARRAY_PASTE2_(x, y)

#define UNION_OF_STRUCT_N_FOR_EACH__(N, type, ...)  UNION_OF_STRUCT_N_ARRAY_PASTE(UNION_OF_STRUCT_N_FOR_EACH_, N)(type, __VA_ARGS__)
#define UNION_OF_STRUCT_N_FOR_EACH_(type, ...)      UNION_OF_STRUCT_N_FOR_EACH__(PP_NARG(__VA_ARGS__), type, __VA_ARGS__)


/**
 * @brief Creates a static array with named elements
 *
 * @code{.c}
 * typedef UNION_OF_STRUCT_N_ARRAY(
 * 	,,
 * 	,,
 * 	a,
 * 	int,
 * 	r, w
 * ) Pipe;
 * @endcode
 *
 * will produce an object which you can use like this:
 *
 * @code{.c}
 * Pipe p;
 * pipe(p.a);
 * write(p.w, buf, strlen(buf));
 * read(p.r, buf, buflen);
 * for ( int i = 0; i < (sizeof(p) / sizeof(*p)); i++ )
 * {
 * 	close(p.a[i]);
 * }
 * @endcode
 */
#define UNION_OF_STRUCT_N_ARRAY(uname_, uvarname_, sname_, svarname_, avarname_, type_, ...) \
	union uname_ \
	{ \
		struct __attribute__ ((__packed__)) sname_\
		{\
			UNION_OF_STRUCT_N_FOR_EACH_(type_, __VA_ARGS__) \
		} svarname_;\
		type_ avarname_[PP_NARG(__VA_ARGS__)]; \
	} uvarname_ \


#endif  // UNION_OF_STRUCT_N_ARRAY_H_
