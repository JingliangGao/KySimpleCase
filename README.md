# Simple test case 

## onnxruntime
### 1. Preparation
```bash
cd onnxruntime_case
chmod +x build-for-debug.sh && ./build-for-debug.sh
```

### 2. Run Case
```bash 
cd onnxruntime_case
./build/ort_test
```

## kytensor-llm
### 1. Preparation
```bash
cd kytensor_llm_case
chmod +x build-for-debug.sh && ./build-for-debug.sh
```

### 2. Run Case
```bash 
cd kytensor_llm_case
llama-simple -m data/Qwen3-0.6B-Q8_0.gguf 
```
