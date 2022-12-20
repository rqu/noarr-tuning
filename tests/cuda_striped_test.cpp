#include <catch2/catch.hpp>

#include <cstdint>

#include <noarr/structures_extended.hpp>
#include "noarr_test_cuda_dummy.hpp"
#include <noarr/structures/interop/cuda_striped.hpp>

TEST_CASE("Cuda striped - 32bit scalar array", "[cuda]") {
	constexpr std::size_t period = 2*4*32;
	constexpr std::size_t nstripes = 32;
	constexpr std::size_t stripe_size = 8;

	static_assert(noarr::cuda_striped_default_period == period);

	auto s = noarr::scalar<std::uint32_t>() ^ noarr::array<'x', 1000>() ^ noarr::cuda_striped<nstripes>();

	REQUIRE((s | noarr::get_size()) == 1000 * nstripes * sizeof(std::uint32_t));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 0))) == 0*period + 0*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 0))) == 0*period + 0*stripe_size + 1*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(2, 0))) == 1*period + 0*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(3, 0))) == 1*period + 0*stripe_size + 1*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(4, 0))) == 2*period + 0*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 0))) == 2*period + 0*stripe_size + 1*sizeof(std::uint32_t));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 1))) == 0*period + 1*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 1))) == 0*period + 1*stripe_size + 1*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(2, 1))) == 1*period + 1*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(3, 1))) == 1*period + 1*stripe_size + 1*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(4, 1))) == 2*period + 1*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 1))) == 2*period + 1*stripe_size + 1*sizeof(std::uint32_t));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 2))) == 0*period + 2*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 2))) == 0*period + 2*stripe_size + 1*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(2, 2))) == 1*period + 2*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(3, 2))) == 1*period + 2*stripe_size + 1*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(4, 2))) == 2*period + 2*stripe_size + 0*sizeof(std::uint32_t));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 2))) == 2*period + 2*stripe_size + 1*sizeof(std::uint32_t));
}

TEST_CASE("Cuda striped - 64bit scalar array", "[cuda]") {
	constexpr std::size_t period = 2*4*32;
	constexpr std::size_t nstripes = 32;
	constexpr std::size_t stripe_size = 8;

	static_assert(noarr::cuda_striped_default_period == period);

	auto s = noarr::scalar<std::uint64_t>() ^ noarr::array<'x', 1000>() ^ noarr::cuda_striped<nstripes>();

	REQUIRE((s | noarr::get_size()) == 1000 * nstripes * sizeof(std::uint64_t));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 0))) == 0*period + 0*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 0))) == 1*period + 0*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(2, 0))) == 2*period + 0*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(3, 0))) == 3*period + 0*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(4, 0))) == 4*period + 0*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 0))) == 5*period + 0*stripe_size);

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 1))) == 0*period + 1*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 1))) == 1*period + 1*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(2, 1))) == 2*period + 1*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(3, 1))) == 3*period + 1*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(4, 1))) == 4*period + 1*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 1))) == 5*period + 1*stripe_size);

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 2))) == 0*period + 2*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 2))) == 1*period + 2*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(2, 2))) == 2*period + 2*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(3, 2))) == 3*period + 2*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(4, 2))) == 4*period + 2*stripe_size);
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 2))) == 5*period + 2*stripe_size);
}

TEST_CASE("Cuda striped - 24bit scalar array - 12 stripes", "[cuda]") {
	struct color { std::uint8_t r, g, b; };

	static_assert(sizeof(color) == 3);

	constexpr std::size_t period = 2*4*32;
	constexpr std::size_t nstripes = 12;
	constexpr std::size_t stripe_size = sizeof(color)*6 + 2; // 6 elems per stripe, 2 bytes padding (to get 4-byte alignment)

	static_assert(noarr::cuda_striped_default_period == period);

	auto s = noarr::scalar<color>() ^ noarr::array<'x', 1000>() ^ noarr::cuda_striped<nstripes>();

	REQUIRE((s | noarr::get_size()) == 167 * period); // 167 = ceil(1000 / 6), where 6 = number of elems per stripe and period

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 0, 0))) == 0*period + 0*stripe_size + 0*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 1, 0))) == 0*period + 0*stripe_size + 1*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 2, 0))) == 0*period + 0*stripe_size + 2*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 3, 0))) == 0*period + 0*stripe_size + 3*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 4, 0))) == 0*period + 0*stripe_size + 4*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 5, 0))) == 0*period + 0*stripe_size + 5*sizeof(color));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>( 6, 0))) == 1*period + 0*stripe_size + 0*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(11, 0))) == 1*period + 0*stripe_size + 5*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(12, 0))) == 2*period + 0*stripe_size + 0*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(17, 0))) == 2*period + 0*stripe_size + 5*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(18, 0))) == 3*period + 0*stripe_size + 0*sizeof(color));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 1))) == 0*period + 1*stripe_size + 0*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 1))) == 0*period + 1*stripe_size + 1*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 1))) == 0*period + 1*stripe_size + 5*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(6, 1))) == 1*period + 1*stripe_size + 0*sizeof(color));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 2))) == 0*period + 2*stripe_size + 0*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 2))) == 0*period + 2*stripe_size + 1*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 2))) == 0*period + 2*stripe_size + 5*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(6, 2))) == 1*period + 2*stripe_size + 0*sizeof(color));

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(0, 11))) == 0*period + 11*stripe_size + 0*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(1, 11))) == 0*period + 11*stripe_size + 1*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(5, 11))) == 0*period + 11*stripe_size + 5*sizeof(color));
	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::cuda_stripe_index>(6, 11))) == 1*period + 11*stripe_size + 0*sizeof(color));
}

TEST_CASE("Cuda striped - 24bit non-scalar array - 12 stripes", "[cuda]") {
	constexpr std::size_t period = 2*4*32;
	constexpr std::size_t nstripes = 12;
	constexpr std::size_t stripe_size = 3*6 + 2; // 6 elems per stripe, 2 bytes padding (to get 4-byte alignment)

	static_assert(noarr::cuda_striped_default_period == period);

	auto color_s = noarr::scalar<std::uint8_t>() ^ noarr::array<'c', 3>();
	auto s = color_s ^ noarr::array<'x', 1000>() ^ noarr::cuda_striped<nstripes, decltype(color_s)>();

	REQUIRE((s | noarr::get_size()) == 167 * period); // 167 = ceil(1000 / 6), where 6 = number of elems per stripe and period

	for(int c = 0; c < 3; c++) {
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 0, c, 0))) == 0*period + 0*stripe_size + 0*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 1, c, 0))) == 0*period + 0*stripe_size + 1*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 2, c, 0))) == 0*period + 0*stripe_size + 2*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 3, c, 0))) == 0*period + 0*stripe_size + 3*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 4, c, 0))) == 0*period + 0*stripe_size + 4*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 5, c, 0))) == 0*period + 0*stripe_size + 5*3 + c);

		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>( 6, c, 0))) == 1*period + 0*stripe_size + 0*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(11, c, 0))) == 1*period + 0*stripe_size + 5*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(12, c, 0))) == 2*period + 0*stripe_size + 0*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(17, c, 0))) == 2*period + 0*stripe_size + 5*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(18, c, 0))) == 3*period + 0*stripe_size + 0*3 + c);

		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(0, c, 1))) == 0*period + 1*stripe_size + 0*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(1, c, 1))) == 0*period + 1*stripe_size + 1*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(5, c, 1))) == 0*period + 1*stripe_size + 5*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(6, c, 1))) == 1*period + 1*stripe_size + 0*3 + c);

		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(0, c, 2))) == 0*period + 2*stripe_size + 0*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(1, c, 2))) == 0*period + 2*stripe_size + 1*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(5, c, 2))) == 0*period + 2*stripe_size + 5*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(6, c, 2))) == 1*period + 2*stripe_size + 0*3 + c);

		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(0, c, 11))) == 0*period + 11*stripe_size + 0*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(1, c, 11))) == 0*period + 11*stripe_size + 1*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(5, c, 11))) == 0*period + 11*stripe_size + 5*3 + c);
		REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(6, c, 11))) == 1*period + 11*stripe_size + 0*3 + c);
	}

	REQUIRE((s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(11, 1, 7))) == 1*period + 7*stripe_size + 5*3 + 1);
	REQUIRE((s | noarr::offset<decltype(color_s)>(noarr::empty_state.with<noarr::index_in<'x'>,    noarr::cuda_stripe_index>(11,    7))) == 1*period + 7*stripe_size + 5*3);
}

TEST_CASE("Cuda striped constexpr arithmetic", "[cuda cearithm]") {
	constexpr std::size_t period = 2*4*32;
	constexpr std::size_t nstripes = 12;
	constexpr std::size_t stripe_size = 3*6 + 2; // 6 elems per stripe, 2 bytes padding (to get 4-byte alignment)

	auto color_s = noarr::scalar<std::uint8_t>() ^ noarr::array<'c', 3>();
	auto s = color_s ^ noarr::array<'x', 1000>() ^ noarr::cuda_striped<nstripes, decltype(color_s)>();

	REQUIRE(decltype(s | noarr::get_size())::value == 167 * period); // 167 = ceil(1000 / 6), where 6 = number of elems per stripe and period
	REQUIRE(decltype(s | noarr::offset(noarr::empty_state.with<noarr::index_in<'x'>, noarr::index_in<'c'>, noarr::cuda_stripe_index>(noarr::idx<11>, noarr::idx<1>, noarr::idx<7>)))::value == 1*period + 7*stripe_size + 5*3 + 1);
	REQUIRE(decltype(s | noarr::offset<decltype(color_s)>(noarr::empty_state.with<noarr::index_in<'x'>,    noarr::cuda_stripe_index>(noarr::idx<11>,                noarr::idx<7>)))::value == 1*period + 7*stripe_size + 5*3);
}
