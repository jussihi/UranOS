; interrupt_relay is the high-level C function
extern interrupt_relay

int_prepare:
	; we store all the registers
	push ds
	push es
	push fs
	push gs
	pusha

	cld

	mov eax, 0x10
	mov ds, eax
	mov es, eax
	lea  ebp, [esp+56]

	push esp
	call interrupt_relay
	add esp, 4

int_exit:
	popa
	pop gs
	pop fs
	pop es
	pop ds

	add esp, 12

	iret

%macro int_1 1
	GLOBAL intr%1:function
	intr%1:
		push ebp
		push dword 0
		push dword %1
		jmp int_prepare
%endmacro

%macro int_2 1
	GLOBAL intr%1:function
	intr%1:
		push  dword [esp]
		mov  [esp+4],ebp
		push dword %1
		jmp int_prepare
%endmacro

int_1  0
int_1  1
int_1  2
int_1  3
int_1  4
int_1  5
int_1  6
int_1  7
int_2  8
int_1  9
int_2 10
int_2 11
int_1 12
int_2 13
int_2 14
int_1 15
int_1 16
int_2 17
int_1 18
int_1 19
int_1 20
int_1 21
int_1 22
int_1 23
int_2 24
int_1 25
int_2 26
int_2 27
int_1 28
int_2 29
int_2 30
int_1 31
int_1 32
int_1 33
int_1 34
int_1 35
int_1 36
int_1 37
int_1 38
int_1 39
int_1 40
int_1 41
int_1 42
int_1 43
int_1 44
int_1 45
int_1 46
int_1 47
int_1 48
int_1 49
int_1 50
int_1 51
int_1 52
int_1 53
int_1 54
int_1 55
int_1 56
int_1 57
int_1 58
int_1 59
int_1 60
int_1 61
int_1 62
int_1 63
int_1 64
int_1 65
int_1 66
int_1 67
int_1 68
int_1 69
int_1 70
int_1 71
int_1 72
int_1 73
int_1 74
int_1 75
int_1 76
int_1 77
int_1 78
int_1 79
int_1 80
int_1 81
int_1 82
int_1 83
int_1 84
int_1 85
int_1 86
int_1 87
int_1 88
int_1 89
int_1 90
int_1 91
int_1 92
int_1 93
int_1 94
int_1 95
int_1 96
int_1 97
int_1 98
int_1 99
int_1 100
int_1 101
int_1 102
int_1 103
int_1 104
int_1 105
int_1 106
int_1 107
int_1 108
int_1 109
int_1 110
int_1 111
int_1 112
int_1 113
int_1 114
int_1 115
int_1 116
int_1 117
int_1 118
int_1 119
int_1 120
int_1 121
int_1 122
int_1 123
int_1 124
int_1 125
int_1 126
int_1 127
int_1 128
int_1 129
int_1 130
int_1 131
int_1 132
int_1 133
int_1 134
int_1 135
int_1 136
int_1 137
int_1 138
int_1 139
int_1 140
int_1 141
int_1 142
int_1 143
int_1 144
int_1 145
int_1 146
int_1 147
int_1 148
int_1 149
int_1 150
int_1 151
int_1 152
int_1 153
int_1 154
int_1 155
int_1 156
int_1 157
int_1 158
int_1 159
int_1 160
int_1 161
int_1 162
int_1 163
int_1 164
int_1 165
int_1 166
int_1 167
int_1 168
int_1 169
int_1 170
int_1 171
int_1 172
int_1 173
int_1 174
int_1 175
int_1 176
int_1 177
int_1 178
int_1 179
int_1 180
int_1 181
int_1 182
int_1 183
int_1 184
int_1 185
int_1 186
int_1 187
int_1 188
int_1 189
int_1 190
int_1 191
int_1 192
int_1 193
int_1 194
int_1 195
int_1 196
int_1 197
int_1 198
int_1 199
int_1 200
int_1 201
int_1 202
int_1 203
int_1 204
int_1 205
int_1 206
int_1 207
int_1 208
int_1 209
int_1 210
int_1 211
int_1 212
int_1 213
int_1 214
int_1 215
int_1 216
int_1 217
int_1 218
int_1 219
int_1 220
int_1 221
int_1 222
int_1 223
int_1 224
int_1 225
int_1 226
int_1 227
int_1 228
int_1 229
int_1 230
int_1 231
int_1 232
int_1 233
int_1 234
int_1 235
int_1 236
int_1 237
int_1 238
int_1 239
int_1 240
int_1 241
int_1 242
int_1 243
int_1 244
int_1 245
int_1 246
int_1 247
int_1 248
int_1 249
int_1 250
int_1 251
int_1 252
int_1 253
int_1 254
int_1 255


GLOBAL interrupt_fpointers
interrupt_fpointers:
	%macro add_int 1
		dd intr%1
	%endmacro

%assign i 0 
%rep    256
    add_int i
%assign i i+1 
%endrep