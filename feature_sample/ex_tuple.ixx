export module ex_tuple;

import dummy;
import <iostream>;
import <compare>;
import <tuple>;
import <string>;

export namespace ex_tuple {

// �֐����畡���̒l��Ԃ�
std::tuple<int, char, ex::Dummy> f()
{
    // std::make_tuple()�͂قƂ�ǂ̏󋵂ŕK�v�Ȃ�
    return { 1, 'a', 20, };
}

void Exec()
{
    // �\���������Ń^�v���𕪉����āA���ꂼ��̗v�f����
    auto [a, b, c] = f();//�����ŃR�s�[�͑���Ȃ�

    std::tuple<int, char, ex::Dummy> t = std::make_tuple(1, 'a', 1);//�R�s�[�͑���Ȃ�

    auto s = std::get<2>(t);//&���Ȃ��ƃR�s�[������
    auto& ref_s = std::get<2>(t);
    auto&& rref_s = std::get<2>(t);
}

}//ex_tuple