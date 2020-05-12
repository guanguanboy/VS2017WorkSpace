#include "draco/compression/encode.h"
#include "draco/core/cycle_timer.h"
#include "draco/io/file_utils.h"
#include "draco/io/mesh_io.h"
#include "draco/io/point_cloud_io.h"

struct Options {
	Options();

	bool is_point_cloud;
	int pos_quantization_bits;
	int tex_coords_quantization_bits;
	bool tex_coords_deleted;
	int normals_quantization_bits;
	bool normals_deleted;
	int generic_quantization_bits;
	bool generic_deleted;
	int compression_level;
	bool use_metadata;
	std::string input;
	std::string output;
};

Options::Options()
	: is_point_cloud(false),
	pos_quantization_bits(11),
	tex_coords_quantization_bits(10),
	tex_coords_deleted(false),
	normals_quantization_bits(7),
	normals_deleted(false),
	generic_quantization_bits(8),
	generic_deleted(false),
	compression_level(7),
	use_metadata(false) {}

int EncodePointCloudToFile(const draco::PointCloud &pc, const std::string &file,
	draco::Encoder *encoder) {
	draco::CycleTimer timer;
	// Encode the geometry.
	draco::EncoderBuffer buffer;
	timer.Start();
	const draco::Status status = encoder->EncodePointCloudToBuffer(pc, &buffer);
	if (!status.ok()) {
		printf("Failed to encode the point cloud.\n");
		printf("%s\n", status.error_msg());
		return -1;
	}
	timer.Stop();
	// Save the encoded geometry into a file.
	if (!draco::WriteBufferToFile(buffer.data(), buffer.size(), file)) {
		printf("Failed to write the output file.\n");
		return -1;
	}
	printf("Encoded point cloud saved to %s (%" PRId64 " ms to encode).\n",
		file.c_str(), timer.GetInMs());
	printf("\nEncoded size = %zu bytes\n\n", buffer.size());
	return 0;
}

#if 1
int main()
{
	Options options;

	std::unique_ptr<draco::PointCloud> pc;
	draco::Mesh *mesh = nullptr;

	std::string input_filename = std::string("D://Code2020//draco-1.3.6//testdata//bun_zipper.ply");

	//auto maybe_mesh =
	//	draco::ReadMeshFromFile(input_filename, true);
	//if (!maybe_mesh.ok()) {
	//	printf("Failed loading the input mesh: %s.\n",
	//		maybe_mesh.status().error_msg());
	//	return -1;
	//}
	//mesh = maybe_mesh.value().get();
	//pc = std::move(maybe_mesh).value();

	//std::string input_filename = std::string("E:\\VS2017WorkSpace\\dracoTest\\x64\\Debug\\bun_zipper.ply");
	auto maybe_pc = draco::ReadPointCloudFromFile(input_filename); //必须要包含stdio_file_reader.cc，该函数中有一个方法用来注册打开文件的函数，如果不包含，会打不开ply文件。
	if (!maybe_pc.ok()) {
		printf("Failed loading the input point cloud: %s.\n",
			maybe_pc.status().error_msg());
		return -1;
	}
	pc = std::move(maybe_pc).value();

	draco::Encoder encoder;

	// Setup encoder options.
	if (options.pos_quantization_bits > 0) {
		encoder.SetAttributeQuantization(draco::GeometryAttribute::POSITION,
			options.pos_quantization_bits);
	}
	if (options.tex_coords_quantization_bits > 0) {
		encoder.SetAttributeQuantization(draco::GeometryAttribute::TEX_COORD,
			options.tex_coords_quantization_bits);
	}
	if (options.normals_quantization_bits > 0) {
		encoder.SetAttributeQuantization(draco::GeometryAttribute::NORMAL,
			options.normals_quantization_bits);
	}
	if (options.generic_quantization_bits > 0) {
		encoder.SetAttributeQuantization(draco::GeometryAttribute::GENERIC,
			options.generic_quantization_bits);
	}

	// Convert compression level to speed (that 0 = slowest, 10 = fastest).
	const int speed = 10 - options.compression_level;

	encoder.SetSpeedOptions(speed, speed);

	std::string output_filename = "bun_zipper.drc";

	int ret = EncodePointCloudToFile(*pc.get(), output_filename, &encoder);
	if (0 != ret)
	{
		printf("compression error.\n");
		return ret;
	}

	return 0;
}

#endif