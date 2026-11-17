#include "raylib.h"

int main(void) {
    // 1. Pencereyi ve Çerçeveyi Başlat
    InitWindow(800, 450, "Retro Sonsuz Araba Oyunu");
    SetTargetFPS(60);

    // 2. Kamera Ayarları (Aracın arkasından takip eden açı)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 3.5f, -7.0f };
    camera.target = (Vector3){ 0.0f, 0.5f, 2.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // 3. Araba Modelini Yükle (Yoksa oyun çökmesin diye otomatik kutu atar)
    Model car = LoadModel("car.glb");
    Vector3 carPos = { 0.0f, 0.0f, 0.0f };

    // 4. Sonsuz Yol Segmentleri (3 parça arka arkaya)
    float roadZ[3] = { 0.0f, 40.0f, 80.0f };
    float roadLength = 40.0f;
    float speed = 0.4f;

    while (!WindowShouldClose()) {
        // --- GÜNCELLEMELER (Mekani̇kler) ---

        // Sol / Sağ Hareket (Yoldan çıkmasın diye sınırlandırıldı)
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && carPos.x > -2.5f) {
            carPos.x -= 0.12f;
        }
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && carPos.x < 2.5f) {
            carPos.x += 0.12f;
        }

        // Aracın Z konumu sabit kalır, yol araca doğru akar (Sonsuz yol hissi)
        for (int i = 0; i < 3; i++) {
            roadZ[i] -= speed;
            // Yol arkada kaybolunca en öne tekrar taşı
            if (roadZ[i] < -20.0f) {
                roadZ[i] += roadLength * 3.0f;
            }
        }

        // --- ÇİZİM AŞAMASI (Grafikler) ---
        BeginDrawing();
            ClearBackground(SKYBLUE); // Gökyüzü rengi

            BeginMode3D(camera);
                // Sonsuz Yol Çizimi (Koyu gri düzlemler)
                for (int i = 0; i < 3; i++) {
                    DrawPlane((Vector3){ 0.0f, -0.01f, roadZ[i] }, (Vector2){ 7.0f, roadLength }, DARKGRAY);
                }

                // Araba Modelini Çiz (Konumu ve boyutu ayarlandı)
                DrawModel(car, carPos, 1.0f, WHITE);
            EndMode3D();

            // Ekran Yazıları (UI)
            DrawText("Kontrol: A - D veya Sol / Sag Yon Tuslari", 15, 15, 18, RAYWHITE);
            DrawText("Durum: Calisiyor", 15, 40, 14, LIGHTGRAY);

        EndDrawing();
    }

    // Belleği Temizle
    UnloadModel(car);
    CloseWindow();

    return 0;
}