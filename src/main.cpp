#include <hittable.hpp>
#include <hittable_list.hpp>
#include <material.hpp>
#include <sphere.hpp>
#include <camera.hpp>
#include <scenes.hpp>
#include <omp.h>
#include <memory>
#include <fstream>
#include <filesystem>


namespace fs = std::filesystem;

struct RenderConfig {
    int scene_id = 1;
    int chunk_size = 16;
    int threads = omp_get_max_threads();
};

RenderConfig parse_args(int argc, char** argv) {
    RenderConfig config;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--scene" && i + 1 < argc) {
            config.scene_id = std::stoi(argv[++i]);
        } else if (arg == "--chunk-size" && i + 1 < argc) {
            config.chunk_size = std::stoi(argv[++i]);
        } else if (arg == "--threads" && i + 1 < argc) {
            config.threads = std::stoi(argv[++i]);
        } else {
            throw std::runtime_error("Unknown or incomplete argument: " + arg);
        }
    }

    return config;
}

void run_log(
    const RenderConfig& config,
    const Scene& scene,
    double total_seconds
) {
    fs::path log_path = fs::path(LOG_FILE);

    bool file_exists = fs::exists(log_path);

    std::ofstream log(log_path, std::ios::app);

    if (!file_exists) {
        log << "scene_id,scene_name,chunk_size,threads,total_seconds\n";
    }

    log << scene.id << ','
        << scene.name << ','
        << config.chunk_size << ','
        << config.threads << ','
        << total_seconds << '\n';

    log.close();
}

int main(int argc, char *argv[]) {
    auto config = parse_args(argc, argv);

    omp_set_num_threads(config.threads);

    auto scene = make_scene(config.scene_id);

    fs::path output_path =
        fs::path(RENDER_DIR) /
        (scene.name +
         "_chunk" + std::to_string(config.chunk_size) +
         "_threads" + std::to_string(config.threads) +
         ".ppm");

    double start = omp_get_wtime();

    scene.cam.render(
        scene.world,
        output_path.string(),
        config.chunk_size,
        config.threads
    );

    double end = omp_get_wtime();

    double total_seconds = end - start;

    std::cout << "\nFinished in " << total_seconds << " seconds.\n";

    run_log(config, scene, total_seconds);

    return 0;
}

