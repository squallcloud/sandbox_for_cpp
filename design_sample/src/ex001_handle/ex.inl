#pragma once

#include "ex001_handle/object.inl"
#include "ex001_handle/object_manager.inl"
#include "ex001_handle/object_handle.inl"

namespace ex001_handle {

// --- メイン関数 ---
int main()
{
    struct Deletor
    {
        Deletor()
        {
            g_object_manager = new ObjectManager();
        }

        ~Deletor()
        {
            delete g_object_manager;
        }
    } deletor;

    
    printf("\n--- オブジェクト作成とアクセス ---\n");

    ObjectHandle handle1 = g_object_manager->CreateObject(10);
    ObjectHandle handle2 = g_object_manager->CreateObject(20);

    if (handle1.IsValid()) {
        handle1->Print();
        (*handle1).value = 100;
        handle1->Print();
    }

    if (handle2.IsValid()) {
        handle2->Print();
    }

    printf("\n--- オブジェクト破棄と無効化のテスト ---\n");

    g_object_manager->DestroyObject(handle1); // handle1 が指すオブジェクトを破棄

    // handle1 は古いバージョンを参照しているので、isValid() が false になるはず
    if (!handle1.IsValid()) {
        printf("handle1 は無効になりました (正しい動作)。\n");
    }

    try {
        handle1->Print(); // ここで例外が発生するはず
    } catch (const std::runtime_error& e) {
        printf("エラー: %s \n", e.what());
    }

    {
        printf("\n--- スロット再利用のテスト ---\n");

        // handle1 が指していたスロットが再利用される
        ObjectHandle handle3 = g_object_manager->CreateObject(30);
        if (handle3.IsValid()) {
            handle3->Print();
            printf("handle3 は handle1 と同じインデックスですが、バージョンは異なります。\n");
        }

        // handle1 は依然として無効なまま
        if (!handle1.IsValid()) {
            std::cout << "古い handle1 は新しいオブジェクトが作成されても無効なままです。\n";
        }
    }

    {
        printf("\n--- 無効なハンドルの直接作成 ---\n");

        ObjectHandle invalid_handle;
        if (!invalid_handle.IsValid()) {
            printf("invalid_handle は最初から無効です。 \n");
        }

        try {
            invalid_handle->Print();
        } catch (const std::runtime_error& e) {
            printf("エラー: %s \n", e.what());
        }
    }

    printf("\n--- 全体のスコープ終了 ---\n");

    return 0;
}

}//ex001_handle