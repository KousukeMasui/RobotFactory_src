#pragma once

#include<crtdbg.h>

class CheckMemoryLeak {
public:
	CheckMemoryLeak() {
		//���������[�N���o�̓E�B���h�E�ɕ\������֐�
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
	~CheckMemoryLeak() {
	}
	/// <summary> �T�v : number��ڂ̃������m�ێ��Ƀu���C�N����悤�ݒ�@</summary>
	/// <param name="number">�o�͉�ʂ�{ xxx }�ɏ����Ă��鐔�l</param>
	void SetBreakPoint(int number) {
		_CrtSetBreakAlloc(number);
	}
};

//���������[�N�������ɉ��̕��͂�ǂ�ł��������B
/*
���������[�N�����Ƃ��A�o�̓E�B���h�E��

Detected memory leaks!
Dumping objects ->
{52992} normal block at 0x000000001E27F290, 72 bytes long.
Data: <                > 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Object dump complete.

�݂����ȕ��͂��o�Ă���B

52992��ڂɊm�ۂ���72�o�C�g�̃����������[�N�����Ƃ����Ӗ��B
����52992��ڂŃ��[�N����ꍇ�́A�����Ńu���C�N���邱�ƂŁA
�������킩�邩������Ȃ��B

_CrtSetBreakAlloc(52992);

���̊֐���52992��ڂ̃������m�ێ��Ƀu���C�N����Ƃ����֐�
*/