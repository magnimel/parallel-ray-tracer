#include <camera.hpp>
#include <scenes.hpp>
#include <omp.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <profiling.hpp>

namespace fs = std::filesystem;

void run_log(
    const RenderConfig& config,
    const Scene& scene,
    double total_seconds
) {
    fs::path log_path = fs::path(LOG_FILE);
    bool file_exists = fs::exists(log_path);

    std::ofstream log(log_path, std::ios::app);

    if (!file_exists) {
        log << "scene_id,scene_name,chunk_size,tile_size,threads,total_seconds\n";
    }

    log << scene.id << ','
        << scene.name << ','
        << config.chunk_size << ','
        << config.tile_size << ','
        << config.threads << ','
        << total_seconds << '\n';
}

int main(int argc, char *argv[]) {
    auto config = parse_args(argc, argv);

    omp_set_num_threads(config.threads);

    auto scene = make_scene(config.scene_id);

    fs::path output_path =
        fs::path(RENDER_DIR) /
        (scene.name +
         "_tile" + std::to_string(config.tile_size) +
         "_threads" + std::to_string(config.threads) +
         ".ppm");

    double start = omp_get_wtime();

    scene.cam.render(scene.world, output_path.string(), config);

    FrameMark;

    double end = omp_get_wtime();

    double total_seconds = end - start;

    std::cout << "\nFinished in " << total_seconds << " seconds.\n";

    run_log(config, scene, total_seconds);

    return 0;
}