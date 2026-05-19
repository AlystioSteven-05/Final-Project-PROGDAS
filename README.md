# Final-Project-PROGDAS

## Judul
Sistem Monitoring Stress Pengendara

## Tujuan
Sistem ini dibuat untuk mencegah insiden road-rage di jalan raya

## Anggota Kelompok 2:
| NPM            | Nama                            | Username GITHUB  |
| -------------- | ------------------------------- | ---------------- |
| 2506535140     | Alystio Steven Xiang            | AlystioSteven-05 |
| 2506593525     | Benedict Jaysen Riofo Panjaitan | ZFrees           |
| 2506611736     | Jeremi Natama Simanjuntak       | Loafietheman     |

## Rubik Penilaian
![Page 1](https://github.com/user-attachments/assets/7b519984-ff03-4bb7-b787-620388d206c6)
![Page 2](https://github.com/user-attachments/assets/4d19a2ce-37da-424b-84b0-35daa9526348)

## Ketentuan
Submission is through EMAS with the following file:
1. Final Program with a .c extension. If separate header files exist, all programs must be zipped into one file.
2. Program executable file (.exe)
3. A Github link (URL is written inside the report). It should be clear who did what
4. Video presentation in Youtube, unlisted. The explation should follow the order of the rubric (see Section III). Duration: 5 – 8 minutes (URL is written inside the report).
5. A report in PDF format. Generally, the report should use font Arial 11 pt, single space, no space before & after paragraph, except the flowchart and source code. The report should include all of this elements:

- Pg 1: Cover
- Pg 2: Video presentation URL & Github URL
- Pg 3: Task division for each group member written in detail & the username in github. Everyone should have clear contribution in making the program, i.e. which block, shich function.
- Pg 4: A brief explanation of the program's theme (no more than 1 page)
- Pg 5 etc: List of variables, arrays, structs, etc., and their uses.
- List of functions and their uses.
- Main program Flowchart. Arial narrow, 9 pt
- Each function flowchart. Arial narrow, 9 pt
- A copy of the source code with the following specifications: font: Lucida Console, 10pt, single space, no space before or after paragraphs, etc.
- Screen capture of the running program (not the code), for all cases.

## Parametrix yang digunakan
**1. Vital Signs**
| Kondisi        | Heart Rate (BPM)                | Tensi (Sistolik) |
| -------------- | ------------------------------- | ---------------- |
| Rileks         | 60 - 80                         | < 120 mmHg       |
| Waspada        | 81 - 100                        | 120 - 129 mmHg   |
| Stress Tinggi  | > 100                           | >= 130 mmHg      |

**2. Keringat(GSR)**
| Kondisi        | microSiemens (µS)               |
| -------------- | ------------------------------- |
| Normal         | < 5 µS                          | 
| Tegang         | 5 - 10 µS                       | 
| Stress         | > 10 µS                         | 

**3. Respiration Rate**
| Kondisi            | Breaths Per Minute(brpm)        |
| ------------------ | ------------------------------- |
| Normal/Rileks      | 12 - 20 brpm                    | 
| Tegang/Napas Cepat | 21 - 25 brpm                    | 
| Emosi/Napas Pendek | > 25 brpm                       | 

**4. Lama Berkendara**
| Kondisi               | Lama Berkendara (menit)         |
| --------------------- | ------------------------------- |
| Baru berkendara       | < 60 Menit                      | 
| Masuk fase jenuh      | 60 - 119 Menit                  | 
| Rawan krisis kognitif | >= 120 Menit nonstop            | 

**5. Suhu Lingkungan**
| Kondisi               | Temperature (Celcius)           |
| --------------------- | ------------------------------- |
| Sejuk / Optimal       | 20 - 25 Celcius                 | 
| Agak Panas            | 26 - 29 Celcius                 | 
| Panas Memicu Emosi    | >= 30 Celcius                   | 

## Jobs Desc
|           Nama             |            Peran           |
| -------------------------  | -------------------------- |
| Alystio Steven Xiang       | Arsitektur program, logika evaluasi parameter fisiologis (Heart Rate, Tekanan Darah, GSR) |
| Benedict Jaysen Riofo Panjaitan | Logika evaluasi pernapasan & durasi, kalkulasi skor total & klasifikasi stress |
| Jeremi Natama Simanjuntak  | Evaluasi suhu lingkungan, tampilan hasil, sistem rekomendasi, validasi input, dokumentasi |

## Workflow Program
```mermaid
---
config:
  layout: elk
  theme: neo
  look: neo
---
flowchart TD
    subgraph subGraphMain["Main Program"]
        A(["Start"]) --> B["int repeat = 1"]
        B --> C["printHeader()"]
        C --> D{"while (repeat)"}
        
        %% Alur di dalam Loop
        D -- Ya --> E["data = inputSensorData()"]
        E --> F["result = calculateStress(data)"]
        F --> G["displayResult(data, result)"]
        G --> H["printRecommendation(result)"]
        H --> I["repeat = askRepeat()"]
        I --> D
        
        %% Keluar dari Loop
        D -- Tidak --> J[/"Tampilkan pesan Terima Kasih & Safe Driving"/]
        J --> K["printSeparator()"]
        K --> L(["End (Return 0)"])
    end
    subgraph subGraphInput["Fungsi: inputSensorData"]
        In1[/"Print: INPUT DATA SENSOR"/] --> In2[/"Input: Heart Rate (BPM)"/]
        In2 --> In2a{"Valid?\n(Angka & > 0)"}
        In2a -- Tidak --> In2
        
        In2a -- Ya --> In3[/"Input: Tekanan Darah (Sistolik)"/]
        In3 --> In3a{"Valid?\n(Angka & > 0)"}
        In3a -- Tidak --> In3
        
        In3a -- Ya --> In4[/"Input: GSR (µS)"/]
        In4 --> In4a{"Valid?\n(Angka & >= 0)"}
        In4a -- Tidak --> In4
        
        In4a -- Ya --> In5[/"Input: Frekuensi Pernapasan"/]
        In5 --> In5a{"Valid?\n(Angka & > 0)"}
        In5a -- Tidak --> In5
        
        In5a -- Ya --> In6[/"Input: Durasi Berkendara (menit)"/]
        In6 --> In6a{"Valid?\n(Angka & >= 0)"}
        In6a -- Tidak --> In6
        
        In6a -- Ya --> In7[/"Input: Suhu Lingkungan (Celsius)"/]
        In7 --> In7a{"Valid?\n(Angka)"}
        In7a -- Tidak --> In7
        
        In7a -- Ya --> InOut["Return data (SensorData)"]
    end
    subgraph subGraphCalc["Fungsi: calculateStress"]
        Calc1["Evaluasi Parameter:\n1. evaluateHeartRate()\n2. evaluateSystolic()\n3. evaluateGSR()\n4. evaluateRespiration()\n5. evaluateDuration()\n6. evaluateTemperature()"]
        
        Calc1 --> Calc2["Hitung total_score =\nPenjumlahan semua skor parameter (6-18)"]
        
        Calc2 --> Calc3{"Apakah\ntotal_score <= 8?"}
        
        Calc3 -- Ya --> CalcStatus1["Level: RILEKS\nSet rekomendasi aman"]
        
        Calc3 -- Tidak --> Calc4{"Apakah\ntotal_score <= 13?"}
        Calc4 -- Ya --> CalcStatus2["Level: WASPADA\nSet rekomendasi istirahat di rest area"]
        Calc4 -- Tidak --> CalcStatus3["Level: STRES TINGGI\nSet rekomendasi SEGERA BERHENTI!"]
        
        CalcStatus1 --> CalcOut["Return result (StressResult)"]
        CalcStatus2 --> CalcOut
        CalcStatus3 --> CalcOut
    end
    subgraph subGraphDisplay["Fungsi: displayResult & printRecommendation"]
        Disp1["Petakan teks status berdasarkan skor\n(level_hr, level_bp, level_gsr, dll)"]
        Disp1 --> Disp2[/"Tampilkan Tabel Hasil Evaluasi Parameter\ndan TOTAL SKOR ke layar"/]
        Disp2 --> Disp3[/"Tampilkan REKOMENDASI\nberdasarkan tingkat stres"/]
    end
    E -.-> In1
    InOut -.-> F
    
    F -.-> Calc1
    CalcOut -.-> G
    
    G -.-> Disp1
    Disp3 -.-> H
```

## Referensi
1. Acuan Heart Rate & Keringat (GSR)
   Healey, J. A., & Picard, R. W. (2005). Detecting Stress During Real-World Driving Tasks Using Physiological Sensors. IEEE Transactions on Intelligent Transportation Systems.
2. Acuan Suhu Lingkungan
   Daanen, H. A. M., dkk. (2003). Driving performance in cold, warm, and thermoneutral environments. Applied Ergonomics.
3. Respirasi & Napas Pendek
   Wilhelm, F. H., Gevirtz, R., & Roth, W. T. (2001). Respiratory dysregulation in anxiety, functional cardiac, and pain disorders. Behavior Modification.
4. Acuan Durasi Berkendara
   Kementerian Kesehatan Republik Indonesia. (2020). Pedoman Kesehatan Keselamatan Berkendara
