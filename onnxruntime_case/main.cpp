#include <onnxruntime_cxx_api.h>

#include <array>
#include <iostream>
#include <vector>

int main() {
    try {
        // 1. 创建环境
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ort-test");

        // 2. 配置 Session
        Ort::SessionOptions session_options;
        session_options.SetIntraOpNumThreads(1);
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

        // 3. 加载模型
        const char* model_path = "simple_add.onnx";
        Ort::Session session(env, model_path, session_options);

        // 4. 准备输入：形状 [1, 3]，值 {1, 2, 3}
        std::array<int64_t, 2> input_shape{1, 3};
        std::vector<float> input_data{1.0f, 2.0f, 3.0f};

        auto memory_info = Ort::MemoryInfo::CreateCpu(
            OrtArenaAllocator, OrtMemTypeDefault);

        Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
            memory_info,
            input_data.data(), input_data.size(),
            input_shape.data(), input_shape.size());

        // 5. 输入输出名字（与本例模型一致）
        const char* input_names[]  = {"X"};
        const char* output_names[] = {"Y"};

        // 6. 推理
        auto outputs = session.Run(
            Ort::RunOptions{nullptr},
            input_names, &input_tensor, 1,
            output_names, 1);

        // 7. 取结果
        float* out = outputs[0].GetTensorMutableData<float>();
        auto out_shape = outputs[0].GetTensorTypeAndShapeInfo().GetShape();

        std::cout << "output shape: [";
        for (size_t i = 0; i < out_shape.size(); ++i) {
            std::cout << out_shape[i] << (i + 1 < out_shape.size() ? ", " : "");
        }
        std::cout << "]\n";

        std::cout << "output data : ";
        for (size_t i = 0; i < 3; ++i) std::cout << out[i] << " ";
        std::cout << "\n";

        // 校验：输入 [1,2,3] + 1 => [2,3,4]
        bool ok = true;
        for (size_t i = 0; i < 3; ++i) {
            if (std::abs(out[i] - (input_data[i] + 1.0f)) > 1e-6) ok = false;
        }
        if (ok) std::cout << "✅ ONNX Runtime 可用，推理结果正确\n";
        else    std::cout << "❌ 推理结果不正确\n";
        return ok ? 0 : 1;
    } catch (const Ort::Exception& e) {
        std::cerr << "ONNX Runtime 异常: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << "\n";
        return 1;
    }
}