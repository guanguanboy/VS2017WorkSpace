#include <cinttypes>

#include "draco/compression/decode.h"
#include "draco/core/cycle_timer.h"
#include "draco/io/file_utils.h"
#include "draco/io/obj_encoder.h"
#include "draco/io/parser_utils.h"
#include "draco/io/ply_encoder.h"

int ReturnError(const draco::Status &status) {
	printf("Failed to decode the input file %s\n", status.error_msg());
	return -1;
}

int main()
{
	std::vector<char> data;

	std::string drc_filename = std::string("E://VS2015Workspace//dracoTest//decoderTest//bun_zipper.drc");
	if (!draco::ReadFileToBuffer(drc_filename, &data)) {
		printf("Failed opening the input file.\n");
		return -1;
	}

	if (data.empty()) {
		printf("Empty input file.\n");
		return -1;
	}

	// Create a draco decoding buffer. Note that no data is copied in this step.
	draco::DecoderBuffer buffer;
	buffer.Init(data.data(), data.size());

	draco::CycleTimer timer;
	// Decode the input data into a geometry.
	std::unique_ptr<draco::PointCloud> pc;
	draco::Mesh *mesh = nullptr;
	auto type_statusor = draco::Decoder::GetEncodedGeometryType(&buffer);
	if (!type_statusor.ok()) {
		return ReturnError(type_statusor.status());
	}
	const draco::EncodedGeometryType geom_type = type_statusor.value();
	if (geom_type == draco::TRIANGULAR_MESH) {
		timer.Start();
		draco::Decoder decoder;
		auto statusor = decoder.DecodeMeshFromBuffer(&buffer);
		if (!statusor.ok()) {
			return ReturnError(statusor.status());
		}
		std::unique_ptr<draco::Mesh> in_mesh = std::move(statusor).value();
		timer.Stop();
		if (in_mesh) {
			mesh = in_mesh.get();
			pc = std::move(in_mesh);
		}
	}
	else if (geom_type == draco::POINT_CLOUD) {
		// Failed to decode it as mesh, so let's try to decode it as a point cloud.
		timer.Start();
		draco::Decoder decoder;
		auto statusor = decoder.DecodePointCloudFromBuffer(&buffer);
		if (!statusor.ok()) {
			return ReturnError(statusor.status());
		}
		pc = std::move(statusor).value();
		timer.Stop();
	}

	if (pc == nullptr) {
		printf("Failed to decode the input file.\n");
		return -1;
	}

	std::string output_ply_filename = std::string("output_bun_zipper.ply");

	draco::PlyEncoder ply_encoder;
	if (mesh) {
		if (!ply_encoder.EncodeToFile(*mesh, output_ply_filename)) {
			printf("Failed to store the decoded mesh as PLY.\n");
			return -1;
		}
	}
	else {
		if (!ply_encoder.EncodeToFile(*pc.get(), output_ply_filename)) {
			printf("Failed to store the decoded point cloud as PLY.\n");
			return -1;
		}
	}

	printf("Decoded geometry saved to %s (%" PRId64 " ms to decode)\n",
		output_ply_filename.c_str(), timer.GetInMs());
	return 0;
}