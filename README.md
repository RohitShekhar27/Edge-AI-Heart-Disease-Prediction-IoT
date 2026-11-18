# 🫀 Heart Disease Prediction Using Edge AI and IoT

An end-to-end **TinyML & IoT** healthcare monitoring system that executes real-time heart disease risk prediction directly on an **ESP32 microcontroller** using bare-metal C++, eliminating cloud inference latency and preserving patient data privacy.

Developed as part of the **IoT (CSBM 632)** M.Tech coursework at the **National Institute of Technology (NIT) Delhi**.

---

## 📌 Problem Statement & Solution

Traditional IoT health wearables stream raw medical vitals to cloud servers for machine learning inference. This creates three critical bottlenecks:
1. **Network & Server Latency:** Dangerous delays during cardiovascular emergencies if Wi-Fi drops or servers lag.
2. **Data Privacy Risks:** Continuous transmission of raw, sensitive health telemetry over networks.
3. **High Power & Bandwidth Usage:** Keeping Wi-Fi radios constantly active drains wearable batteries rapidly.

**Our Edge AI Solution:**  
We decoupled diagnostic computation from the cloud. A lightweight **Logistic Regression** model is trained offline in Python, converted into a standalone C++ header (`model.h`) via `micromlgen`, and deployed directly onto the ESP32. The microcontroller evaluates vitals locally in real time and transmits only lightweight telemetry and the final binary prediction (`0` = Healthy, `1` = Risk) to **ThingSpeak** for physician visualization.

---

## 🏗️ System Architecture

1. **Offline Training (Google Colab):** Data preprocessing and model benchmarking on the UCI Heart Disease dataset (303 samples, 13 clinical features, 80/20 train-test split).
2. **TinyML Conversion (`micromlgen`):** Freezing learned Logistic Regression weights and exporting them into bare-metal C++ (`model.h`).
3. **On-Device Edge Inference (ESP32 / Wokwi):** Running `classifier.predict()` natively on the ESP32's 32-bit processor with minimal SRAM usage.
4. **Cloud Telemetry Visualization (ThingSpeak):** Logging simulated vitals and local diagnostic flags via `HTTPClient` REST GET requests.
   - **Field 1:** Resting Blood Pressure
   - **Field 2:** Maximum Heart Rate
   - **Field 3:** Local Edge Diagnosis (`0.00` = Normal, `1.00` = Defective Heart Risk)

---

## 📊 Model Benchmarks

| Model | Validation Accuracy | Edge Deployment Suitability (ESP32 SRAM) |
| :--- | :---: | :--- |
| **Logistic Regression (Selected)** | **81.97%** | **Optimal** — Basic dot products + Sigmoid; negligible SRAM footprint |
| Random Forest | 80.33% | Moderate — Multiple decision trees increase memory overhead |
| LSTM (Deep Learning) | — | **Unsuitable** — Requires 3D tensors & dense matrices; exceeds 520 KB SRAM budget |

---

## 🔗 Live Workspaces & Demo

- 📓 **Google Colab (ML Training & Export):** [Open Notebook](https://colab.research.google.com/drive/1wgi-CTl_E5srPwUHt75e7Y-GLEKn7tkv?usp=sharing)
- ⚡ **Wokwi Simulation (Live ESP32 Edge Inference):** [Run Simulator](https://wokwi.com/projects/479282233640573953)
- 📈 **ThingSpeak Dashboard (Channel ID: 3570447):** [View Live Charts](https://thingspeak.mathworks.com/channels/3570447)
- 🎥 **Zip file with demonstration Video:** [Watch on Google Drive](https://drive.google.com/file/d/1m70dzC4-zpKcwbW7TWlav5LNV4HHCFdq/view?usp=drive_link)

---

## 📂 Repository Structure

```text
├── 01_Report/
│   └── Heart_Disease_Prediction_with_IoT.pdf    # Final M.Tech Project Report
├── 02_Source_Code/
│   ├── ML_Training_Colab/
│   │   ├── Heart_Disease_Prediction.ipynb       # Model training & micromlgen export
│   ├── ESP32_Wokwi/
│   │   ├── sketch.ino                           # Main ESP32 C++ firmware & HTTPClient logic
│   │   ├── model.h                              # Exported Logistic Regression C++ header
│   │   └── diagram.json                         # Wokwi circuit configuration
├── 03_Presentation/
│   └── Heart_Disease_EdgeAI_Presentation.html   # Project Slide Deck
└── README.md
