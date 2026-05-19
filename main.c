#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCT DEFINITIONS

typedef struct {
    int   heart_rate;       // BPM
    int   systolic;         // mmHg
    float gsr;              // µS (microsiemens)
    int   respiration_rate; // breaths per minute
    int   drive_duration;   // minutes 
    float temperature;      // Celsius 
} SensorData;

typedef struct {
    int   hr_score;         // 1-3
    int   bp_score;         // 1-3
    int   gsr_score;        // 1-3
    int   rr_score;         // 1-3
    int   dur_score;        // 1-3
    int   temp_score;       // 1-3
    int   total_score;
    char  stress_level[30];
    char  recommendation[200];
} StressResult;

// FUNCTION

void        printHeader(void);
void        printSeparator(void);
SensorData  inputSensorData(void);
int         evaluateHeartRate(int bpm);
int         evaluateSystolic(int systolic);
int         evaluateGSR(float gsr);
int         evaluateRespiration(int rr);
int         evaluateDuration(int duration);
int         evaluateTemperature(float temp);
StressResult calculateStress(SensorData data);
void        displayResult(SensorData data, StressResult result);
void        printRecommendation(StressResult result);
int         askRepeat(void);

// MAIN PROGRAM

int main(void) {
    int repeat = 1;

    printHeader();

    while (repeat) {
        SensorData   data   = inputSensorData();
        StressResult result = calculateStress(data);
        displayResult(data, result);
        printRecommendation(result);
        repeat = askRepeat();
    }

    printf("\n  Terima kasih telah menggunakan Stress Monitor.\n");
    printf("  Selalu jaga kesehatan dan berkendara dengan aman!\n");
    printSeparator();

    return 0;
}

// PRINT HEADER

void printHeader(void) {
    printf("\n");
    printf("  ============================================================\n");
    printf("      SISTEM MONITORING STRESS PENGENDARA\n");
    printf("      ProgDas 01 - Group 02\n");
    printf("      SDG 3: Good Health and Well-Being\n");
    printf("  ============================================================\n");
}

void printSeparator(void) {
    printf("  ============================================================\n");
}

// INPUT DATA

SensorData inputSensorData(void) {
    SensorData data;

    printf("  [INPUT DATA SENSOR]\n");
    printf("  ------------------------------------------------------------\n");

    printf("  1. Heart Rate (BPM)            : ");
    while (scanf("%d", &data.heart_rate) != 1 || data.heart_rate <= 0) {
        printf("     Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }

    printf("  2. Tekanan Darah Sistolik (mmHg): ");
    while (scanf("%d", &data.systolic) != 1 || data.systolic <= 0) {
        printf("     Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }

    printf("  3. GSR - Galvanic Skin Response\n");
    printf("     (Konduktansi kulit dalam µS) : ");
    while (scanf("%f", &data.gsr) != 1 || data.gsr < 0) {
        printf("     Input tidak valid. Masukkan angka >= 0: ");
        while (getchar() != '\n');
    }

    printf("  4. Frekuensi Pernapasan (napas/menit): ");
    while (scanf("%d", &data.respiration_rate) != 1 || data.respiration_rate <= 0) {
        printf("     Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }

    printf("  5. Durasi Berkendara (menit)   : ");
    while (scanf("%d", &data.drive_duration) != 1 || data.drive_duration < 0) {
        printf("     Input tidak valid. Masukkan angka >= 0: ");
        while (getchar() != '\n');
    }

    printf("  6. Suhu Lingkungan (Celsius)   : ");
    while (scanf("%f", &data.temperature) != 1) {
        printf("     Input tidak valid. Masukkan angka: ");
        while (getchar() != '\n');
    }

    return data;
}

// EVALUATE HEART RATE
// Return: 1=Rileks, 2=Waspada, 3=Stres Tinggi

int evaluateHeartRate(int bpm) {
    if (bpm >= 60 && bpm <= 80)
        return 1; // Rileks
    else if (bpm >= 81 && bpm <= 100)
        return 2; // Waspada
    else if (bpm > 100)
        return 3; // Stres Tinggi
    else
        return 2; // Di bawah 60 juga waspada
}

// EVALUATE SYSTOLIC BLOOD PRESSURE
// Return: 1=Normal, 2=Waspada, 3=Tinggi

int evaluateSystolic(int systolic) {
    if (systolic < 120)
        return 1;
    else if (systolic >= 120 && systolic <= 129)
        return 2;
    else
        return 3; // >= 130
}

// EVALUATE GSR (Galvanic Skin Response)
// Return: 1=Normal, 2=Tegang, 3=Stres Tinggi

int evaluateGSR(float gsr) {
    if (gsr < 5.0f)
        return 1;
    else if (gsr >= 5.0f && gsr <= 10.0f)
        return 2;
    else
        return 3; // > 10
}

// EVALUATE RESPIRATION RATE
// Return: 1=Normal, 2=Waspada, 3=Stres Tinggi

int evaluateRespiration(int rr) {
    if (rr >= 12 && rr <= 20)
        return 1;
    else if (rr >= 21 && rr <= 25)
        return 2;
    else if (rr > 25)
        return 3;
    else
        return 2; // < 12 juga tidak normal
}

// EVALUATE DRIVE DURATION
// Return: 1=Aman, 2=Jenuh, 3=Rawan Krisis

int evaluateDuration(int duration) {
    if (duration < 60)
        return 1;
    else if (duration >= 60 && duration <= 119)
        return 2;
    else
        return 3; // >= 120
}

// EVALUATE TEMPERATURE
// Return: 1=Sejuk, 2=Agak Panas, 3=Panas

int evaluateTemperature(float temp) {
    if (temp >= 20.0f && temp <= 25.0f)
        return 1;
    else if (temp >= 26.0f && temp <= 29.0f)
        return 2;
    else
        return 3; // >= 30 or < 20
}

// CALCULATE STRESS LEVEL
// Menghitung skor total dan menentukan tingkat stress

StressResult calculateStress(SensorData data) {
    StressResult result;

    // Evaluate each parameter
    result.hr_score   = evaluateHeartRate(data.heart_rate);
    result.bp_score   = evaluateSystolic(data.systolic);
    result.gsr_score  = evaluateGSR(data.gsr);
    result.rr_score   = evaluateRespiration(data.respiration_rate);
    result.dur_score  = evaluateDuration(data.drive_duration);
    result.temp_score = evaluateTemperature(data.temperature);

    // Total score: 6 (all rileks) to 18 (all stres tinggi)
    result.total_score = result.hr_score + result.bp_score + result.gsr_score + result.rr_score + result.dur_score + result.temp_score;

    // Classify stress level
    if (result.total_score <= 8) {
        strcpy(result.stress_level, "RILEKS");
        strcpy(result.recommendation,
            "Kondisi Anda optimal untuk berkendara. "
            "Tetap waspada dan nikmati perjalanan Anda!");
    } else if (result.total_score <= 13) {
        strcpy(result.stress_level, "WASPADA");
        strcpy(result.recommendation,
            "Tanda-tanda awal stres terdeteksi. "
            "Pertimbangkan untuk menarik napas dalam, "
            "kurangi kecepatan, atau berhenti sejenak di rest area.");
    } else {
        strcpy(result.stress_level, "STRES TINGGI");
        strcpy(result.recommendation,
            "PERINGATAN: Tingkat stres Anda sangat tinggi! "
            "SEGERA berhenti dan beristirahat minimal 15-30 menit. "
            "Hindari berkendara agresif. Hubungi seseorang jika perlu.");
    }

    return result;
}

// DISPLAY RESULT
// Menampilkan hasil evaluasi setiap parameter

void displayResult(SensorData data, StressResult result) {
    char *level_hr[]   = {"", "Rileks (60-80 BPM)", "Waspada (81-100 BPM)", "Stres Tinggi (>100 BPM)"};
    char *level_bp[]   = {"", "Normal (<120 mmHg)", "Perbatasan (120-129)", "Tinggi (>=130 mmHg)"};
    char *level_gsr[]  = {"", "Normal/Rileks (<5 uS)", "Keringat Dingin (5-10 uS)", "Keringat Bercucuran (>10 uS)"};
    char *level_rr[]   = {"", "Normal (12-20 /mnt)", "Napas Cepat (21-25 /mnt)", "Hiperventilasi (>25 /mnt)"};
    char *level_dur[]  = {"", "Aman (<60 mnt)", "Jenuh (60-119 mnt)", "Rawan Krisis (>=120 mnt)"};
    char *level_temp[] = {"", "Sejuk (20-25 C)", "Agak Panas (26-29 C)", "Panas Emosi (>=30 C)"};

    printf("\n");
    printSeparator();
    printf("  [HASIL EVALUASI PARAMETER]\n");
    printf("  ------------------------------------------------------------\n");
    printf("  %-38s Skor  Status\n", "Parameter");
    printf("  ------------------------------------------------------------------\n");

    printf("  %-38s [%d/3]  %s\n",
        "1. Heart Rate", result.hr_score, level_hr[result.hr_score]);

    printf("  %-38s [%d/3]  %s\n",
        "2. Tekanan Darah Sistolik", result.bp_score, level_bp[result.bp_score]);

    printf("  %-38s [%d/3]  %s\n",
        "3. Galvanic Skin Response (GSR)", result.gsr_score, level_gsr[result.gsr_score]);

    printf("  %-38s [%d/3]  %s\n",
        "4. Frekuensi Pernapasan", result.rr_score, level_rr[result.rr_score]);

    printf("  %-38s [%d/3]  %s\n",
        "5. Durasi Berkendara", result.dur_score, level_dur[result.dur_score]);

    printf("  %-38s [%d/3]  %s\n",
        "6. Suhu Lingkungan", result.temp_score, level_temp[result.temp_score]);

    printf("  ------------------------------------------------------------------\n");
    printf("  TOTAL SKOR: %d / 18\n", result.total_score);
    printf("  ------------------------------------------------------------------\n");

    // Stress level with visual emphasis
    if (result.total_score <= 8) {
        printf("  >> TINGKAT STRESS: [ %s ] <<\n", result.stress_level);
    } else if (result.total_score <= 13) {
        printf("  >> TINGKAT STRESS: [ %s ] <<\n", result.stress_level);
    } else {
        printf("  >> TINGKAT STRESS: [ %s ] <<\n", result.stress_level);
    }
}

// PRINT RECOMMENDATION
// Menampilkan rekomendasi berdasarkan tingkat stres

void printRecommendation(StressResult result) {
    printf("  ------------------------------------------------------------\n");
    printf("  REKOMENDASI:\n");
    printf("  %s\n", result.recommendation);
    printSeparator();
}

// ASK REPEAT
// Menanyakan apakah pengguna ingin melakukan pengukuran ulang
// Return: 1=Ya, 0=Tidak

int askRepeat(void) {
    char choice;
    printf("\n  Lakukan pengukuran ulang? (y/n): ");
    while (getchar() != '\n'); /* flush buffer */
    scanf("%c", &choice);
    return (choice == 'y' || choice == 'Y') ? 1 : 0;
}