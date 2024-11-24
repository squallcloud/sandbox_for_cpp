import ex_component_oriented;

import util;
#include <chrono>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ex_component_oriented {

// シンプルなコンポーネント指向
namespace normal_component {

class GameObject;

class IComponent
{
public:
    virtual void Update() {
        //TODO:
    }

    void SetOwner(GameObject* in_obj) {
        owner_ = in_obj;
    }

protected:
    GameObject* owner_{};
};

class GameObject
{
    using components_map_type = std::unordered_map<std::type_index, std::shared_ptr<IComponent>>;

public:
    template<typename CompType>
    std::weak_ptr<CompType> AddComponent() {
        auto&& new_comp = std::make_shared<CompType>();
        components_[typeid(CompType)] = new_comp;
        new_comp->SetOwner(this);
        return new_comp;
    }

    template<typename CompType>
    std::weak_ptr<CompType> GetComponent() {
        return std::static_pointer_cast<CompType>(components_[typeid(CompType)]);
    }

    void Update() {
        for (auto&& comp : components_) {
            comp.second->Update();
        }
    }

private:
    components_map_type components_{};
};

#define DEFINE_TEST_COMPONENT(TYPE_NAME) class TYPE_NAME : public IComponent { public: int a = 0; };
DEFINE_TEST_COMPONENT(TestComponent0);
DEFINE_TEST_COMPONENT(TestComponent1);
DEFINE_TEST_COMPONENT(TestComponent2);
DEFINE_TEST_COMPONENT(TestComponent3);
DEFINE_TEST_COMPONENT(TestComponent4);
DEFINE_TEST_COMPONENT(TestComponent5);
DEFINE_TEST_COMPONENT(TestComponent6);
DEFINE_TEST_COMPONENT(TestComponent7);
DEFINE_TEST_COMPONENT(TestComponent8);
DEFINE_TEST_COMPONENT(TestComponent9);
#undef DEFINE_TEST_COMPONENT

class RigidbodyComponent : public IComponent
{
public:
    void Update() override {
        auto&& test0 = owner_->GetComponent<TestComponent0>().lock().get();
        auto&& test1 = owner_->GetComponent<TestComponent1>().lock().get();
        auto&& test2 = owner_->GetComponent<TestComponent2>().lock().get();
        auto&& test3 = owner_->GetComponent<TestComponent3>().lock().get();
        auto&& test4 = owner_->GetComponent<TestComponent4>().lock().get();
        auto&& test5 = owner_->GetComponent<TestComponent5>().lock().get();
        auto&& test6 = owner_->GetComponent<TestComponent6>().lock().get();
        auto&& test7 = owner_->GetComponent<TestComponent7>().lock().get();
        auto&& test8 = owner_->GetComponent<TestComponent8>().lock().get();
        auto&& test9 = owner_->GetComponent<TestComponent9>().lock().get();

        a = test0->a +
            test1->a +
            test2->a +
            test3->a +
            test4->a +
            test5->a +
            test6->a +
            test7->a +
            test8->a +
            test9->a;
    }

    int a = 0;
};

}//normal_component

// データが連続するコンポーネント指向
namespace data_component {

class GameObject;

// コンポーネントの基底クラス
class IComponent
{
public:
    virtual void Update() {
        //TODO:
    }
    void SetOwner(GameObject* in_obj) {
        owner_ = in_obj;
    }

protected:
    GameObject* owner_{};
};

// ComponentArrayの基底クラス
class IComponentArray
{
public:
    virtual void Update() {
        //TODO:
    }
};

// コンポーネントを種類ごとに管理するコンテナクラス
template<typename CompType>
class ComponentArray : public IComponentArray
{
    using base_type = IComponentArray;
    using self_type = ComponentArray<CompType>;

public:
    ComponentArray() = default;

    // このクラスが管理するコンポーネントの更新関数を全て実行する
    void Update() override {
        for (auto&& comp : components_) {
            comp.Update();
        }
    }

    // コンポーネントを追加し、追加したコンポーネントを返す
    CompType* AddComponent() {
        components_.emplace_back();
        return &components_.back();
    }

    // CompTypeIDを取得する関数
    static inline const size_t GetID() {
        if (!self_type::comp_type_id_) {
            //この関数を初めて読んだ時にIDを発行
            self_type::comp_type_id_ = ++next_comp_type_id_;
        }

        return self_type::comp_type_id_;
    }

private:
    // このコンテナクラスが管理するコンポーネントが持つ一意なID
    inline static size_t comp_type_id_{};
    inline static size_t next_comp_type_id_{};

    std::vector<CompType> components_{};
};

// コンポーネントを管理するクラス
class ComponentManager
{
    using comp_map_type = std::unordered_map<size_t, std::shared_ptr<IComponentArray>>;

public:
    static void Update() {
        Instance().update();
    }

    template<typename CompType>
    static CompType* AddComponent() {
        return Instance().add_component<CompType>();
    }

private:
    static ComponentManager& Instance() {
        static ComponentManager instance;
        return instance;
    }

    // 全てのコンポーネントの更新関数を実行する
    void update() {
        for (auto&& compArray : type_to_comp_array_) {
            compArray.second->Update();
        }
    }

    template<typename CompType>
    CompType* add_component() {
        const size_t type = ComponentArray<CompType>::GetID();
        if (type_to_comp_array_.find(type) == type_to_comp_array_.end()) {
            type_to_comp_array_[type] = std::make_shared<ComponentArray<CompType>>();
        }

        return std::static_pointer_cast<ComponentArray<CompType>>(type_to_comp_array_[type])->AddComponent();
    }

    ComponentManager() = default;


private:
    comp_map_type type_to_comp_array_{};
};

// ゲームオブジェクト1つとそれに紐づくコンポーネントを管理するクラス
class GameObject
{
public:
    // ComponentManagerにコンポーネントを追加し、このクラスと紐づける
    template<typename CompType>
    CompType* AddComponent() {
        const size_t type = ComponentArray<CompType>::GetID();
        auto&& new_comp = ComponentManager::AddComponent<CompType>();
        if (type_to_comp_.size() <= type) {
            type_to_comp_.resize(type + 1, nullptr);
        }
        type_to_comp_[type] = static_cast<void*>(new_comp);
        new_comp->SetOwner(this);
        return new_comp;
    }

    template<typename CompType>
    CompType* GetComponent() {
        return static_cast<CompType*>(type_to_comp_[ComponentArray<CompType>::GetID()]);
    }

private:
    std::vector<void*> type_to_comp_{};
};

#define DEFINE_TEST_COMPONENT(TYPE_NAME) class TYPE_NAME : public IComponent { public: int a = 0; };
DEFINE_TEST_COMPONENT(TestComponent0);
DEFINE_TEST_COMPONENT(TestComponent1);
DEFINE_TEST_COMPONENT(TestComponent2);
DEFINE_TEST_COMPONENT(TestComponent3);
DEFINE_TEST_COMPONENT(TestComponent4);
DEFINE_TEST_COMPONENT(TestComponent5);
DEFINE_TEST_COMPONENT(TestComponent6);
DEFINE_TEST_COMPONENT(TestComponent7);
DEFINE_TEST_COMPONENT(TestComponent8);
DEFINE_TEST_COMPONENT(TestComponent9);
#undef DEFINE_TEST_COMPONENT

class RigidbodyComponent :public IComponent
{
public:
    void Update()override {
        auto&& test0 = owner_->GetComponent<TestComponent0>();
        auto&& test1 = owner_->GetComponent<TestComponent1>();
        auto&& test2 = owner_->GetComponent<TestComponent2>();
        auto&& test3 = owner_->GetComponent<TestComponent3>();
        auto&& test4 = owner_->GetComponent<TestComponent4>();
        auto&& test5 = owner_->GetComponent<TestComponent5>();
        auto&& test6 = owner_->GetComponent<TestComponent6>();
        auto&& test7 = owner_->GetComponent<TestComponent7>();
        auto&& test8 = owner_->GetComponent<TestComponent8>();
        auto&& test9 = owner_->GetComponent<TestComponent9>();
        a = test0->a +
            test1->a +
            test2->a +
            test3->a +
            test4->a +
            test5->a +
            test6->a +
            test7->a +
            test8->a +
            test9->a;
    }

    int a = 0;
};

}//data_component


void Exec()
{
    //constexpr size_t TestNum = 100000000;
    constexpr size_t TestNum = 10000;

    ex::util::duration_type::rep normal_time{}, data_time{};

    if constexpr (1) {

        std::vector<normal_component::GameObject> normal_objs;
        normal_objs.reserve(TestNum);

        for (size_t i = 0; i < TestNum; i++) {
            normal_objs.emplace_back();
            auto& obj = normal_objs.back();
            obj.AddComponent<normal_component::TestComponent0>();
            obj.AddComponent<normal_component::TestComponent1>();
            obj.AddComponent<normal_component::TestComponent2>();
            obj.AddComponent<normal_component::TestComponent3>();
            obj.AddComponent<normal_component::TestComponent4>();
            obj.AddComponent<normal_component::TestComponent5>();
            obj.AddComponent<normal_component::TestComponent6>();
            obj.AddComponent<normal_component::TestComponent7>();
            obj.AddComponent<normal_component::TestComponent8>();
            obj.AddComponent<normal_component::TestComponent9>();
            obj.AddComponent<normal_component::RigidbodyComponent>();
        }

        const auto&& dur = ex::util::profile_func([&]() {
            for (auto&& obj : normal_objs) {
                obj.Update();
            }
        });

        const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        ::printf("Normal\t%10lld ns \n", nanoseconds);

        normal_time = nanoseconds;
    }

    if constexpr (1) {

        std::vector<data_component::GameObject> data_objs;
        data_objs.reserve(TestNum);

        for (size_t i = 0; i < TestNum; i++) {
            data_objs.emplace_back();
            auto& obj = data_objs.back();
            obj.AddComponent<data_component::TestComponent0>();
            obj.AddComponent<data_component::TestComponent1>();
            obj.AddComponent<data_component::TestComponent2>();
            obj.AddComponent<data_component::TestComponent3>();
            obj.AddComponent<data_component::TestComponent4>();
            obj.AddComponent<data_component::TestComponent5>();
            obj.AddComponent<data_component::TestComponent6>();
            obj.AddComponent<data_component::TestComponent7>();
            obj.AddComponent<data_component::TestComponent8>();
            obj.AddComponent<data_component::TestComponent9>();
            obj.AddComponent<data_component::RigidbodyComponent>();
        }

        const auto&& dur = ex::util::profile_func([&]() {
            data_component::ComponentManager::Update();
        });

        const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        ::printf("Data\t%10lld ns \n", nanoseconds);

        data_time = nanoseconds;
    }

    {
        const double ratio = ((double)data_time / (double)normal_time) * 100.0;
        ::printf("%.2lf %% \n", ratio);
    }
}

}//ex_component_oriented