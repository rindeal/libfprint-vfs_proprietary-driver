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

#ifndef _TRACE_H_
#define _TRACE_H_


#include <stdio.h>


// https://stackoverflow.com/a/41367919/2566213
#define _TRACE_STRIPPATH_(s) \
	( \
		sizeof(s) > 2   && (s)[sizeof(s) - 2]   == '/' ? (s) + sizeof(s) - 1 : \
		sizeof(s) > 3   && (s)[sizeof(s) - 3]   == '/' ? (s) + sizeof(s) - 2 : \
		sizeof(s) > 4   && (s)[sizeof(s) - 4]   == '/' ? (s) + sizeof(s) - 3 : \
		sizeof(s) > 5   && (s)[sizeof(s) - 5]   == '/' ? (s) + sizeof(s) - 4 : \
		sizeof(s) > 6   && (s)[sizeof(s) - 6]   == '/' ? (s) + sizeof(s) - 5 : \
		sizeof(s) > 7   && (s)[sizeof(s) - 7]   == '/' ? (s) + sizeof(s) - 6 : \
		sizeof(s) > 8   && (s)[sizeof(s) - 8]   == '/' ? (s) + sizeof(s) - 7 : \
		sizeof(s) > 9   && (s)[sizeof(s) - 9]   == '/' ? (s) + sizeof(s) - 8 : \
		sizeof(s) > 10  && (s)[sizeof(s) - 10]  == '/' ? (s) + sizeof(s) - 9 : \
		sizeof(s) > 11  && (s)[sizeof(s) - 11]  == '/' ? (s) + sizeof(s) - 10 : \
		sizeof(s) > 11  && (s)[sizeof(s) - 11]  == '/' ? (s) + sizeof(s) - 10 : \
		sizeof(s) > 12  && (s)[sizeof(s) - 12]  == '/' ? (s) + sizeof(s) - 11 : \
		sizeof(s) > 13  && (s)[sizeof(s) - 13]  == '/' ? (s) + sizeof(s) - 12 : \
		sizeof(s) > 14  && (s)[sizeof(s) - 14]  == '/' ? (s) + sizeof(s) - 13 : \
		sizeof(s) > 15  && (s)[sizeof(s) - 15]  == '/' ? (s) + sizeof(s) - 14 : \
		sizeof(s) > 16  && (s)[sizeof(s) - 16]  == '/' ? (s) + sizeof(s) - 15 : \
		sizeof(s) > 17  && (s)[sizeof(s) - 17]  == '/' ? (s) + sizeof(s) - 16 : \
		sizeof(s) > 18  && (s)[sizeof(s) - 18]  == '/' ? (s) + sizeof(s) - 17 : \
		sizeof(s) > 19  && (s)[sizeof(s) - 19]  == '/' ? (s) + sizeof(s) - 18 : \
		sizeof(s) > 20  && (s)[sizeof(s) - 20]  == '/' ? (s) + sizeof(s) - 19 : \
		sizeof(s) > 21  && (s)[sizeof(s) - 21]  == '/' ? (s) + sizeof(s) - 20 : \
		sizeof(s) > 22  && (s)[sizeof(s) - 22]  == '/' ? (s) + sizeof(s) - 21 : \
		sizeof(s) > 23  && (s)[sizeof(s) - 23]  == '/' ? (s) + sizeof(s) - 22 : \
		sizeof(s) > 24  && (s)[sizeof(s) - 24]  == '/' ? (s) + sizeof(s) - 23 : \
		sizeof(s) > 25  && (s)[sizeof(s) - 25]  == '/' ? (s) + sizeof(s) - 24 : \
		sizeof(s) > 26  && (s)[sizeof(s) - 26]  == '/' ? (s) + sizeof(s) - 25 : \
		sizeof(s) > 27  && (s)[sizeof(s) - 27]  == '/' ? (s) + sizeof(s) - 26 : \
		sizeof(s) > 28  && (s)[sizeof(s) - 28]  == '/' ? (s) + sizeof(s) - 27 : \
		sizeof(s) > 29  && (s)[sizeof(s) - 29]  == '/' ? (s) + sizeof(s) - 28 : \
		sizeof(s) > 30  && (s)[sizeof(s) - 30]  == '/' ? (s) + sizeof(s) - 29 : \
		sizeof(s) > 31  && (s)[sizeof(s) - 31]  == '/' ? (s) + sizeof(s) - 30 : \
		sizeof(s) > 32  && (s)[sizeof(s) - 32]  == '/' ? (s) + sizeof(s) - 31 : \
		sizeof(s) > 33  && (s)[sizeof(s) - 33]  == '/' ? (s) + sizeof(s) - 32 : \
		sizeof(s) > 34  && (s)[sizeof(s) - 34]  == '/' ? (s) + sizeof(s) - 33 : \
		sizeof(s) > 35  && (s)[sizeof(s) - 35]  == '/' ? (s) + sizeof(s) - 34 : \
		sizeof(s) > 36  && (s)[sizeof(s) - 36]  == '/' ? (s) + sizeof(s) - 35 : \
		sizeof(s) > 37  && (s)[sizeof(s) - 37]  == '/' ? (s) + sizeof(s) - 36 : \
		sizeof(s) > 38  && (s)[sizeof(s) - 38]  == '/' ? (s) + sizeof(s) - 37 : \
		sizeof(s) > 39  && (s)[sizeof(s) - 39]  == '/' ? (s) + sizeof(s) - 38 : \
		sizeof(s) > 40  && (s)[sizeof(s) - 40]  == '/' ? (s) + sizeof(s) - 39 : \
		sizeof(s) > 41  && (s)[sizeof(s) - 41]  == '/' ? (s) + sizeof(s) - 40 : \
		sizeof(s) > 42  && (s)[sizeof(s) - 42]  == '/' ? (s) + sizeof(s) - 41 : \
		sizeof(s) > 43  && (s)[sizeof(s) - 43]  == '/' ? (s) + sizeof(s) - 42 : \
		sizeof(s) > 44  && (s)[sizeof(s) - 44]  == '/' ? (s) + sizeof(s) - 43 : \
		sizeof(s) > 45  && (s)[sizeof(s) - 45]  == '/' ? (s) + sizeof(s) - 44 : \
		sizeof(s) > 46  && (s)[sizeof(s) - 46]  == '/' ? (s) + sizeof(s) - 45 : \
		sizeof(s) > 47  && (s)[sizeof(s) - 47]  == '/' ? (s) + sizeof(s) - 46 : \
		sizeof(s) > 48  && (s)[sizeof(s) - 48]  == '/' ? (s) + sizeof(s) - 47 : \
		sizeof(s) > 49  && (s)[sizeof(s) - 49]  == '/' ? (s) + sizeof(s) - 48 : \
		sizeof(s) > 50  && (s)[sizeof(s) - 50]  == '/' ? (s) + sizeof(s) - 49 : \
		sizeof(s) > 51  && (s)[sizeof(s) - 51]  == '/' ? (s) + sizeof(s) - 50 : \
		sizeof(s) > 52  && (s)[sizeof(s) - 52]  == '/' ? (s) + sizeof(s) - 51 : \
		sizeof(s) > 53  && (s)[sizeof(s) - 53]  == '/' ? (s) + sizeof(s) - 52 : \
		sizeof(s) > 54  && (s)[sizeof(s) - 54]  == '/' ? (s) + sizeof(s) - 53 : \
		sizeof(s) > 55  && (s)[sizeof(s) - 55]  == '/' ? (s) + sizeof(s) - 54 : \
		sizeof(s) > 56  && (s)[sizeof(s) - 56]  == '/' ? (s) + sizeof(s) - 55 : \
		sizeof(s) > 57  && (s)[sizeof(s) - 57]  == '/' ? (s) + sizeof(s) - 56 : \
		sizeof(s) > 58  && (s)[sizeof(s) - 58]  == '/' ? (s) + sizeof(s) - 57 : \
		sizeof(s) > 59  && (s)[sizeof(s) - 59]  == '/' ? (s) + sizeof(s) - 58 : \
		sizeof(s) > 60  && (s)[sizeof(s) - 60]  == '/' ? (s) + sizeof(s) - 59 : \
		sizeof(s) > 61  && (s)[sizeof(s) - 61]  == '/' ? (s) + sizeof(s) - 60 : \
		sizeof(s) > 62  && (s)[sizeof(s) - 62]  == '/' ? (s) + sizeof(s) - 61 : \
		sizeof(s) > 63  && (s)[sizeof(s) - 63]  == '/' ? (s) + sizeof(s) - 62 : \
		sizeof(s) > 64  && (s)[sizeof(s) - 64]  == '/' ? (s) + sizeof(s) - 63 : \
		sizeof(s) > 65  && (s)[sizeof(s) - 65]  == '/' ? (s) + sizeof(s) - 64 : \
		sizeof(s) > 66  && (s)[sizeof(s) - 66]  == '/' ? (s) + sizeof(s) - 65 : \
		sizeof(s) > 67  && (s)[sizeof(s) - 67]  == '/' ? (s) + sizeof(s) - 66 : \
		sizeof(s) > 68  && (s)[sizeof(s) - 68]  == '/' ? (s) + sizeof(s) - 67 : \
		sizeof(s) > 69  && (s)[sizeof(s) - 69]  == '/' ? (s) + sizeof(s) - 68 : \
		sizeof(s) > 70  && (s)[sizeof(s) - 70]  == '/' ? (s) + sizeof(s) - 69 : \
		sizeof(s) > 71  && (s)[sizeof(s) - 71]  == '/' ? (s) + sizeof(s) - 70 : \
		sizeof(s) > 72  && (s)[sizeof(s) - 72]  == '/' ? (s) + sizeof(s) - 71 : \
		sizeof(s) > 73  && (s)[sizeof(s) - 73]  == '/' ? (s) + sizeof(s) - 72 : \
		sizeof(s) > 74  && (s)[sizeof(s) - 74]  == '/' ? (s) + sizeof(s) - 73 : \
		sizeof(s) > 75  && (s)[sizeof(s) - 75]  == '/' ? (s) + sizeof(s) - 74 : \
		sizeof(s) > 76  && (s)[sizeof(s) - 76]  == '/' ? (s) + sizeof(s) - 75 : \
		sizeof(s) > 77  && (s)[sizeof(s) - 77]  == '/' ? (s) + sizeof(s) - 76 : \
		sizeof(s) > 78  && (s)[sizeof(s) - 78]  == '/' ? (s) + sizeof(s) - 77 : \
		sizeof(s) > 79  && (s)[sizeof(s) - 79]  == '/' ? (s) + sizeof(s) - 78 : \
		sizeof(s) > 80  && (s)[sizeof(s) - 80]  == '/' ? (s) + sizeof(s) - 79 : \
		sizeof(s) > 81  && (s)[sizeof(s) - 81]  == '/' ? (s) + sizeof(s) - 80 : \
		sizeof(s) > 82  && (s)[sizeof(s) - 82]  == '/' ? (s) + sizeof(s) - 81 : \
		sizeof(s) > 83  && (s)[sizeof(s) - 83]  == '/' ? (s) + sizeof(s) - 82 : \
		sizeof(s) > 84  && (s)[sizeof(s) - 84]  == '/' ? (s) + sizeof(s) - 83 : \
		sizeof(s) > 85  && (s)[sizeof(s) - 85]  == '/' ? (s) + sizeof(s) - 84 : \
		sizeof(s) > 86  && (s)[sizeof(s) - 86]  == '/' ? (s) + sizeof(s) - 85 : \
		sizeof(s) > 87  && (s)[sizeof(s) - 87]  == '/' ? (s) + sizeof(s) - 86 : \
		sizeof(s) > 88  && (s)[sizeof(s) - 88]  == '/' ? (s) + sizeof(s) - 87 : \
		sizeof(s) > 89  && (s)[sizeof(s) - 89]  == '/' ? (s) + sizeof(s) - 88 : \
		sizeof(s) > 90  && (s)[sizeof(s) - 90]  == '/' ? (s) + sizeof(s) - 89 : \
		sizeof(s) > 91  && (s)[sizeof(s) - 91]  == '/' ? (s) + sizeof(s) - 90 : \
		sizeof(s) > 92  && (s)[sizeof(s) - 92]  == '/' ? (s) + sizeof(s) - 91 : \
		sizeof(s) > 93  && (s)[sizeof(s) - 93]  == '/' ? (s) + sizeof(s) - 92 : \
		sizeof(s) > 94  && (s)[sizeof(s) - 94]  == '/' ? (s) + sizeof(s) - 93 : \
		sizeof(s) > 95  && (s)[sizeof(s) - 95]  == '/' ? (s) + sizeof(s) - 94 : \
		sizeof(s) > 96  && (s)[sizeof(s) - 96]  == '/' ? (s) + sizeof(s) - 95 : \
		sizeof(s) > 97  && (s)[sizeof(s) - 97]  == '/' ? (s) + sizeof(s) - 96 : \
		sizeof(s) > 98  && (s)[sizeof(s) - 98]  == '/' ? (s) + sizeof(s) - 97 : \
		sizeof(s) > 99  && (s)[sizeof(s) - 99]  == '/' ? (s) + sizeof(s) - 98 : \
		sizeof(s) > 100 && (s)[sizeof(s) - 100] == '/' ? (s) + sizeof(s) - 99 : \
		sizeof(s) > 101 && (s)[sizeof(s) - 101] == '/' ? (s) + sizeof(s) - 100 : \
		sizeof(s) > 102 && (s)[sizeof(s) - 102] == '/' ? (s) + sizeof(s) - 101 : \
		sizeof(s) > 103 && (s)[sizeof(s) - 103] == '/' ? (s) + sizeof(s) - 102 : \
		sizeof(s) > 104 && (s)[sizeof(s) - 104] == '/' ? (s) + sizeof(s) - 103 : \
		sizeof(s) > 105 && (s)[sizeof(s) - 105] == '/' ? (s) + sizeof(s) - 104 : \
		sizeof(s) > 106 && (s)[sizeof(s) - 106] == '/' ? (s) + sizeof(s) - 105 : \
		sizeof(s) > 107 && (s)[sizeof(s) - 107] == '/' ? (s) + sizeof(s) - 106 : \
		sizeof(s) > 108 && (s)[sizeof(s) - 108] == '/' ? (s) + sizeof(s) - 107 : \
		sizeof(s) > 109 && (s)[sizeof(s) - 109] == '/' ? (s) + sizeof(s) - 108 : \
		sizeof(s) > 110 && (s)[sizeof(s) - 110] == '/' ? (s) + sizeof(s) - 109 : \
		sizeof(s) > 111 && (s)[sizeof(s) - 111] == '/' ? (s) + sizeof(s) - 110 : \
		sizeof(s) > 112 && (s)[sizeof(s) - 112] == '/' ? (s) + sizeof(s) - 111 : \
		sizeof(s) > 113 && (s)[sizeof(s) - 113] == '/' ? (s) + sizeof(s) - 112 : \
		sizeof(s) > 114 && (s)[sizeof(s) - 114] == '/' ? (s) + sizeof(s) - 113 : \
		sizeof(s) > 115 && (s)[sizeof(s) - 115] == '/' ? (s) + sizeof(s) - 114 : \
		sizeof(s) > 116 && (s)[sizeof(s) - 116] == '/' ? (s) + sizeof(s) - 115 : \
		sizeof(s) > 117 && (s)[sizeof(s) - 117] == '/' ? (s) + sizeof(s) - 116 : \
		sizeof(s) > 118 && (s)[sizeof(s) - 118] == '/' ? (s) + sizeof(s) - 117 : \
		sizeof(s) > 119 && (s)[sizeof(s) - 119] == '/' ? (s) + sizeof(s) - 118 : \
		sizeof(s) > 120 && (s)[sizeof(s) - 120] == '/' ? (s) + sizeof(s) - 119 : \
		sizeof(s) > 121 && (s)[sizeof(s) - 121] == '/' ? (s) + sizeof(s) - 120 : \
		sizeof(s) > 122 && (s)[sizeof(s) - 122] == '/' ? (s) + sizeof(s) - 121 : \
		sizeof(s) > 123 && (s)[sizeof(s) - 123] == '/' ? (s) + sizeof(s) - 122 : \
		sizeof(s) > 124 && (s)[sizeof(s) - 124] == '/' ? (s) + sizeof(s) - 123 : \
		sizeof(s) > 125 && (s)[sizeof(s) - 125] == '/' ? (s) + sizeof(s) - 124 : \
		sizeof(s) > 126 && (s)[sizeof(s) - 126] == '/' ? (s) + sizeof(s) - 125 : \
		sizeof(s) > 127 && (s)[sizeof(s) - 127] == '/' ? (s) + sizeof(s) - 126 : \
		sizeof(s) > 128 && (s)[sizeof(s) - 128] == '/' ? (s) + sizeof(s) - 127 : \
		sizeof(s) > 129 && (s)[sizeof(s) - 129] == '/' ? (s) + sizeof(s) - 128 : \
		sizeof(s) > 130 && (s)[sizeof(s) - 130] == '/' ? (s) + sizeof(s) - 129 : \
		sizeof(s) > 131 && (s)[sizeof(s) - 131] == '/' ? (s) + sizeof(s) - 130 : \
		sizeof(s) > 132 && (s)[sizeof(s) - 132] == '/' ? (s) + sizeof(s) - 131 : \
		sizeof(s) > 133 && (s)[sizeof(s) - 133] == '/' ? (s) + sizeof(s) - 132 : \
		sizeof(s) > 134 && (s)[sizeof(s) - 134] == '/' ? (s) + sizeof(s) - 133 : \
		sizeof(s) > 135 && (s)[sizeof(s) - 135] == '/' ? (s) + sizeof(s) - 134 : \
		sizeof(s) > 136 && (s)[sizeof(s) - 136] == '/' ? (s) + sizeof(s) - 135 : \
		sizeof(s) > 137 && (s)[sizeof(s) - 137] == '/' ? (s) + sizeof(s) - 136 : \
		sizeof(s) > 138 && (s)[sizeof(s) - 138] == '/' ? (s) + sizeof(s) - 137 : \
		sizeof(s) > 139 && (s)[sizeof(s) - 139] == '/' ? (s) + sizeof(s) - 138 : \
		sizeof(s) > 140 && (s)[sizeof(s) - 140] == '/' ? (s) + sizeof(s) - 139 : \
		sizeof(s) > 141 && (s)[sizeof(s) - 141] == '/' ? (s) + sizeof(s) - 140 : \
		sizeof(s) > 142 && (s)[sizeof(s) - 142] == '/' ? (s) + sizeof(s) - 141 : \
		sizeof(s) > 143 && (s)[sizeof(s) - 143] == '/' ? (s) + sizeof(s) - 142 : \
		sizeof(s) > 144 && (s)[sizeof(s) - 144] == '/' ? (s) + sizeof(s) - 143 : \
		sizeof(s) > 145 && (s)[sizeof(s) - 145] == '/' ? (s) + sizeof(s) - 144 : \
		sizeof(s) > 146 && (s)[sizeof(s) - 146] == '/' ? (s) + sizeof(s) - 145 : \
		sizeof(s) > 147 && (s)[sizeof(s) - 147] == '/' ? (s) + sizeof(s) - 146 : \
		sizeof(s) > 148 && (s)[sizeof(s) - 148] == '/' ? (s) + sizeof(s) - 147 : \
		sizeof(s) > 149 && (s)[sizeof(s) - 149] == '/' ? (s) + sizeof(s) - 148 : \
		sizeof(s) > 150 && (s)[sizeof(s) - 150] == '/' ? (s) + sizeof(s) - 149 : \
		sizeof(s) > 151 && (s)[sizeof(s) - 151] == '/' ? (s) + sizeof(s) - 150 : \
		sizeof(s) > 152 && (s)[sizeof(s) - 152] == '/' ? (s) + sizeof(s) - 151 : \
		sizeof(s) > 153 && (s)[sizeof(s) - 153] == '/' ? (s) + sizeof(s) - 152 : \
		sizeof(s) > 154 && (s)[sizeof(s) - 154] == '/' ? (s) + sizeof(s) - 153 : \
		sizeof(s) > 155 && (s)[sizeof(s) - 155] == '/' ? (s) + sizeof(s) - 154 : \
		sizeof(s) > 156 && (s)[sizeof(s) - 156] == '/' ? (s) + sizeof(s) - 155 : \
		sizeof(s) > 157 && (s)[sizeof(s) - 157] == '/' ? (s) + sizeof(s) - 156 : \
		sizeof(s) > 158 && (s)[sizeof(s) - 158] == '/' ? (s) + sizeof(s) - 157 : \
		sizeof(s) > 159 && (s)[sizeof(s) - 159] == '/' ? (s) + sizeof(s) - 158 : \
		sizeof(s) > 160 && (s)[sizeof(s) - 160] == '/' ? (s) + sizeof(s) - 159 : \
		sizeof(s) > 161 && (s)[sizeof(s) - 161] == '/' ? (s) + sizeof(s) - 160 : \
		sizeof(s) > 162 && (s)[sizeof(s) - 162] == '/' ? (s) + sizeof(s) - 161 : \
		sizeof(s) > 163 && (s)[sizeof(s) - 163] == '/' ? (s) + sizeof(s) - 162 : \
		sizeof(s) > 164 && (s)[sizeof(s) - 164] == '/' ? (s) + sizeof(s) - 163 : \
		sizeof(s) > 165 && (s)[sizeof(s) - 165] == '/' ? (s) + sizeof(s) - 164 : \
		sizeof(s) > 166 && (s)[sizeof(s) - 166] == '/' ? (s) + sizeof(s) - 165 : \
		sizeof(s) > 167 && (s)[sizeof(s) - 167] == '/' ? (s) + sizeof(s) - 166 : \
		sizeof(s) > 168 && (s)[sizeof(s) - 168] == '/' ? (s) + sizeof(s) - 167 : \
		sizeof(s) > 169 && (s)[sizeof(s) - 169] == '/' ? (s) + sizeof(s) - 168 : \
		sizeof(s) > 170 && (s)[sizeof(s) - 170] == '/' ? (s) + sizeof(s) - 169 : \
		sizeof(s) > 171 && (s)[sizeof(s) - 171] == '/' ? (s) + sizeof(s) - 170 : \
		sizeof(s) > 172 && (s)[sizeof(s) - 172] == '/' ? (s) + sizeof(s) - 171 : \
		sizeof(s) > 173 && (s)[sizeof(s) - 173] == '/' ? (s) + sizeof(s) - 172 : \
		sizeof(s) > 174 && (s)[sizeof(s) - 174] == '/' ? (s) + sizeof(s) - 173 : \
		sizeof(s) > 175 && (s)[sizeof(s) - 175] == '/' ? (s) + sizeof(s) - 174 : \
		sizeof(s) > 176 && (s)[sizeof(s) - 176] == '/' ? (s) + sizeof(s) - 175 : \
		sizeof(s) > 177 && (s)[sizeof(s) - 177] == '/' ? (s) + sizeof(s) - 176 : \
		sizeof(s) > 178 && (s)[sizeof(s) - 178] == '/' ? (s) + sizeof(s) - 177 : \
		sizeof(s) > 179 && (s)[sizeof(s) - 179] == '/' ? (s) + sizeof(s) - 178 : \
		sizeof(s) > 180 && (s)[sizeof(s) - 180] == '/' ? (s) + sizeof(s) - 179 : \
		sizeof(s) > 181 && (s)[sizeof(s) - 181] == '/' ? (s) + sizeof(s) - 180 : \
		sizeof(s) > 182 && (s)[sizeof(s) - 182] == '/' ? (s) + sizeof(s) - 181 : \
		sizeof(s) > 183 && (s)[sizeof(s) - 183] == '/' ? (s) + sizeof(s) - 182 : \
		sizeof(s) > 184 && (s)[sizeof(s) - 184] == '/' ? (s) + sizeof(s) - 183 : \
		sizeof(s) > 185 && (s)[sizeof(s) - 185] == '/' ? (s) + sizeof(s) - 184 : \
		sizeof(s) > 186 && (s)[sizeof(s) - 186] == '/' ? (s) + sizeof(s) - 185 : \
		sizeof(s) > 187 && (s)[sizeof(s) - 187] == '/' ? (s) + sizeof(s) - 186 : \
		sizeof(s) > 188 && (s)[sizeof(s) - 188] == '/' ? (s) + sizeof(s) - 187 : \
		sizeof(s) > 189 && (s)[sizeof(s) - 189] == '/' ? (s) + sizeof(s) - 188 : \
		sizeof(s) > 190 && (s)[sizeof(s) - 190] == '/' ? (s) + sizeof(s) - 189 : \
		sizeof(s) > 191 && (s)[sizeof(s) - 191] == '/' ? (s) + sizeof(s) - 190 : \
		sizeof(s) > 192 && (s)[sizeof(s) - 192] == '/' ? (s) + sizeof(s) - 191 : \
		sizeof(s) > 193 && (s)[sizeof(s) - 193] == '/' ? (s) + sizeof(s) - 192 : \
		sizeof(s) > 194 && (s)[sizeof(s) - 194] == '/' ? (s) + sizeof(s) - 193 : \
		sizeof(s) > 195 && (s)[sizeof(s) - 195] == '/' ? (s) + sizeof(s) - 194 : \
		sizeof(s) > 196 && (s)[sizeof(s) - 196] == '/' ? (s) + sizeof(s) - 195 : \
		sizeof(s) > 197 && (s)[sizeof(s) - 197] == '/' ? (s) + sizeof(s) - 196 : \
		sizeof(s) > 198 && (s)[sizeof(s) - 198] == '/' ? (s) + sizeof(s) - 197 : \
		sizeof(s) > 199 && (s)[sizeof(s) - 199] == '/' ? (s) + sizeof(s) - 198 : \
		sizeof(s) > 200 && (s)[sizeof(s) - 200] == '/' ? (s) + sizeof(s) - 199 : \
		sizeof(s) > 201 && (s)[sizeof(s) - 201] == '/' ? (s) + sizeof(s) - 200 : \
		sizeof(s) > 202 && (s)[sizeof(s) - 202] == '/' ? (s) + sizeof(s) - 201 : \
		sizeof(s) > 203 && (s)[sizeof(s) - 203] == '/' ? (s) + sizeof(s) - 202 : \
		sizeof(s) > 204 && (s)[sizeof(s) - 204] == '/' ? (s) + sizeof(s) - 203 : \
		sizeof(s) > 205 && (s)[sizeof(s) - 205] == '/' ? (s) + sizeof(s) - 204 : \
		sizeof(s) > 206 && (s)[sizeof(s) - 206] == '/' ? (s) + sizeof(s) - 205 : \
		sizeof(s) > 207 && (s)[sizeof(s) - 207] == '/' ? (s) + sizeof(s) - 206 : \
		sizeof(s) > 208 && (s)[sizeof(s) - 208] == '/' ? (s) + sizeof(s) - 207 : \
		sizeof(s) > 209 && (s)[sizeof(s) - 209] == '/' ? (s) + sizeof(s) - 208 : \
		sizeof(s) > 210 && (s)[sizeof(s) - 210] == '/' ? (s) + sizeof(s) - 209 : \
		sizeof(s) > 211 && (s)[sizeof(s) - 211] == '/' ? (s) + sizeof(s) - 210 : \
		sizeof(s) > 212 && (s)[sizeof(s) - 212] == '/' ? (s) + sizeof(s) - 211 : \
		sizeof(s) > 213 && (s)[sizeof(s) - 213] == '/' ? (s) + sizeof(s) - 212 : \
		sizeof(s) > 214 && (s)[sizeof(s) - 214] == '/' ? (s) + sizeof(s) - 213 : \
		sizeof(s) > 215 && (s)[sizeof(s) - 215] == '/' ? (s) + sizeof(s) - 214 : \
		sizeof(s) > 216 && (s)[sizeof(s) - 216] == '/' ? (s) + sizeof(s) - 215 : \
		sizeof(s) > 217 && (s)[sizeof(s) - 217] == '/' ? (s) + sizeof(s) - 216 : \
		sizeof(s) > 218 && (s)[sizeof(s) - 218] == '/' ? (s) + sizeof(s) - 217 : \
		sizeof(s) > 219 && (s)[sizeof(s) - 219] == '/' ? (s) + sizeof(s) - 218 : \
		sizeof(s) > 220 && (s)[sizeof(s) - 220] == '/' ? (s) + sizeof(s) - 219 : \
		sizeof(s) > 221 && (s)[sizeof(s) - 221] == '/' ? (s) + sizeof(s) - 220 : \
		sizeof(s) > 222 && (s)[sizeof(s) - 222] == '/' ? (s) + sizeof(s) - 221 : \
		sizeof(s) > 223 && (s)[sizeof(s) - 223] == '/' ? (s) + sizeof(s) - 222 : \
		sizeof(s) > 224 && (s)[sizeof(s) - 224] == '/' ? (s) + sizeof(s) - 223 : \
		sizeof(s) > 225 && (s)[sizeof(s) - 225] == '/' ? (s) + sizeof(s) - 224 : \
		sizeof(s) > 226 && (s)[sizeof(s) - 226] == '/' ? (s) + sizeof(s) - 225 : \
		sizeof(s) > 227 && (s)[sizeof(s) - 227] == '/' ? (s) + sizeof(s) - 226 : \
		sizeof(s) > 228 && (s)[sizeof(s) - 228] == '/' ? (s) + sizeof(s) - 227 : \
		sizeof(s) > 229 && (s)[sizeof(s) - 229] == '/' ? (s) + sizeof(s) - 228 : \
		sizeof(s) > 230 && (s)[sizeof(s) - 230] == '/' ? (s) + sizeof(s) - 229 : \
		sizeof(s) > 231 && (s)[sizeof(s) - 231] == '/' ? (s) + sizeof(s) - 230 : \
		sizeof(s) > 232 && (s)[sizeof(s) - 232] == '/' ? (s) + sizeof(s) - 231 : \
		sizeof(s) > 233 && (s)[sizeof(s) - 233] == '/' ? (s) + sizeof(s) - 232 : \
		sizeof(s) > 234 && (s)[sizeof(s) - 234] == '/' ? (s) + sizeof(s) - 233 : \
		sizeof(s) > 235 && (s)[sizeof(s) - 235] == '/' ? (s) + sizeof(s) - 234 : \
		sizeof(s) > 236 && (s)[sizeof(s) - 236] == '/' ? (s) + sizeof(s) - 235 : \
		sizeof(s) > 237 && (s)[sizeof(s) - 237] == '/' ? (s) + sizeof(s) - 236 : \
		sizeof(s) > 238 && (s)[sizeof(s) - 238] == '/' ? (s) + sizeof(s) - 237 : \
		sizeof(s) > 239 && (s)[sizeof(s) - 239] == '/' ? (s) + sizeof(s) - 238 : \
		sizeof(s) > 240 && (s)[sizeof(s) - 240] == '/' ? (s) + sizeof(s) - 239 : \
		sizeof(s) > 241 && (s)[sizeof(s) - 241] == '/' ? (s) + sizeof(s) - 240 : \
		sizeof(s) > 242 && (s)[sizeof(s) - 242] == '/' ? (s) + sizeof(s) - 241 : \
		sizeof(s) > 243 && (s)[sizeof(s) - 243] == '/' ? (s) + sizeof(s) - 242 : \
		sizeof(s) > 244 && (s)[sizeof(s) - 244] == '/' ? (s) + sizeof(s) - 243 : \
		sizeof(s) > 245 && (s)[sizeof(s) - 245] == '/' ? (s) + sizeof(s) - 244 : \
		sizeof(s) > 246 && (s)[sizeof(s) - 246] == '/' ? (s) + sizeof(s) - 245 : \
		sizeof(s) > 247 && (s)[sizeof(s) - 247] == '/' ? (s) + sizeof(s) - 246 : \
		sizeof(s) > 248 && (s)[sizeof(s) - 248] == '/' ? (s) + sizeof(s) - 247 : \
		sizeof(s) > 249 && (s)[sizeof(s) - 249] == '/' ? (s) + sizeof(s) - 248 : \
		sizeof(s) > 250 && (s)[sizeof(s) - 250] == '/' ? (s) + sizeof(s) - 249 : \
		sizeof(s) > 251 && (s)[sizeof(s) - 251] == '/' ? (s) + sizeof(s) - 250 : \
		sizeof(s) > 252 && (s)[sizeof(s) - 252] == '/' ? (s) + sizeof(s) - 251 : \
		sizeof(s) > 253 && (s)[sizeof(s) - 253] == '/' ? (s) + sizeof(s) - 252 : \
		sizeof(s) > 254 && (s)[sizeof(s) - 254] == '/' ? (s) + sizeof(s) - 253 : \
		sizeof(s) > 255 && (s)[sizeof(s) - 255] == '/' ? (s) + sizeof(s) - 254 : \
		(s) \
	)


#define TRACE()  fprintf(stderr, "TRACE %s: %s() [%d]\n", _TRACE_STRIPPATH_(__FILE__), __func__, __LINE__)


#endif  // _TRACE_H_
