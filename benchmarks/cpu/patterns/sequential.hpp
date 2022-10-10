/*
 * This file is part of covfie, a part of the ACTS project
 *
 * Copyright (c) 2022 CERN
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <covfie/core/backend/primitive/constant.hpp>
#include <covfie/core/field.hpp>
#include <covfie/core/vector.hpp>

struct Sequential1D : covfie::benchmark::AccessPattern<Sequential1D> {
    struct parameters {
        std::size_t xs;
    };

    static constexpr std::array<std::string_view, 1> parameter_names = {"X"};

    template <typename backend_t>
    static void
    iteration(const parameters & p, const covfie::field_view<backend_t> & f, ::benchmark::State &)
    {
        for (unsigned long x = 0; x < p.xs; ++x) {
            ::benchmark::DoNotOptimize(f.at(static_cast<float>(x)));
        }
    }

    static std::vector<std::vector<int64_t>> get_parameter_ranges()
    {
        return {{1, 8, 64, 512, 4096}};
    }

    static parameters get_parameters(benchmark::State & state)
    {
        return {static_cast<std::size_t>(state.range(0))};
    }

    template <typename S, std::size_t N>
    static covfie::benchmark::counters get_counters(const parameters & p)
    {
        return {p.xs, p.xs * N * sizeof(S), 0};
    }
};

struct Sequential2D : covfie::benchmark::AccessPattern<Sequential2D> {
    struct parameters {
        std::size_t xs, ys;
    };

    static constexpr std::array<std::string_view, 2> parameter_names = {
        "X", "Y"};

    template <typename backend_t>
    static void
    iteration(const parameters & p, const covfie::field_view<backend_t> & f, ::benchmark::State &)
    {
        for (unsigned long x = 0; x < p.xs; ++x) {
            for (unsigned long y = 0; y < p.ys; ++y) {
                ::benchmark::DoNotOptimize(
                    f.at(static_cast<float>(x), static_cast<float>(y))
                );
            }
        }
    }

    static std::vector<std::vector<int64_t>> get_parameter_ranges()
    {
        return {{1, 8, 64, 512, 4096}, {1, 8, 64, 512, 4096}};
    }

    static parameters get_parameters(benchmark::State & state)
    {
        return {
            static_cast<std::size_t>(state.range(0)),
            static_cast<std::size_t>(state.range(1))};
    }

    template <typename S, std::size_t N>
    static covfie::benchmark::counters get_counters(const parameters & p)
    {
        return {p.xs * p.ys, p.xs * p.ys * 2 * sizeof(float), 0};
    }
};

struct Sequential3D : covfie::benchmark::AccessPattern<Sequential3D> {
    struct parameters {
        std::size_t xs, ys, zs;
    };

    static constexpr std::array<std::string_view, 3> parameter_names = {
        "X", "Y", "Z"};

    template <typename backend_t>
    static void
    iteration(const parameters & p, const covfie::field_view<backend_t> & f, ::benchmark::State &)
    {
        for (unsigned long x = 0; x < p.xs; ++x) {
            for (unsigned long y = 0; y < p.ys; ++y) {
                for (unsigned long z = 0; z < p.zs; ++z) {
                    ::benchmark::DoNotOptimize(f.at(x, y, z));
                }
            }
        }
    }

    static std::vector<std::vector<int64_t>> get_parameter_ranges()
    {
        return {{201}, {201}, {301}};
    }

    static parameters get_parameters(benchmark::State & state)
    {
        return {
            static_cast<std::size_t>(state.range(0)),
            static_cast<std::size_t>(state.range(1)),
            static_cast<std::size_t>(state.range(2))};
    }

    template <typename S, std::size_t N>
    static covfie::benchmark::counters get_counters(const parameters & p)
    {
        return {p.xs * p.ys * p.zs, p.xs * p.ys * p.zs * N * sizeof(S), 0};
    }
};

struct Sequential3DZYX : covfie::benchmark::AccessPattern<Sequential3DZYX> {
    struct parameters {
        std::size_t xs, ys, zs;
    };

    static constexpr std::array<std::string_view, 3> parameter_names = {
        "X", "Y", "Z"};

    template <typename backend_t>
    static void
    iteration(const parameters & p, const covfie::field_view<backend_t> & f, ::benchmark::State &)
    {
        for (unsigned long z = 0; z < p.zs; ++z) {
            for (unsigned long y = 0; y < p.ys; ++y) {
                for (unsigned long x = 0; x < p.xs; ++x) {
                    ::benchmark::DoNotOptimize(f.at(x, y, z));
                }
            }
        }
    }

    static std::vector<std::vector<int64_t>> get_parameter_ranges()
    {
        return {{201}, {201}, {301}};
    }

    static parameters get_parameters(benchmark::State & state)
    {
        return {
            static_cast<std::size_t>(state.range(0)),
            static_cast<std::size_t>(state.range(1)),
            static_cast<std::size_t>(state.range(2))};
    }

    template <typename S, std::size_t N>
    static covfie::benchmark::counters get_counters(const parameters & p)
    {
        return {p.xs * p.ys * p.zs, p.xs * p.ys * p.zs * N * sizeof(S), 0};
    }
};
