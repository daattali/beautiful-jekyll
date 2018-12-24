/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file testVoxelComplex.cpp
 * @ingroup Tests
 * @author Pablo Hernandez-Cerdan (\c pablo.hernandez.cerdan@outlook.com)
 * Institute of Fundamental Sciences. Massey University.
 * Palmerston North, New Zealand
 *
 * @date 2018/01/01
 *
 * Testing class for VoxelComplex.
 *
 * This file is part of the DGtal library.
 */

#include "DGtal/base/SetFunctions.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/CubicalComplexFunctions.h"
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/topology/KhalimskyCellHashFunctions.h"
#include "DGtal/topology/VoxelComplex.h"
#include "DGtal/topology/VoxelComplexFunctions.h"
#include "DGtalCatch.h"
#include <iostream>
#include <unordered_map>

#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/topology/NeighborhoodConfigurations.h"
#include "DGtal/topology/tables/NeighborhoodTables.h"
// #include <DGtal/io/viewers/Viewer3D.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////
// Fixture for object from a diamond set and DT26_6 topology.
///////////////////////////////////////////////////////////////////////////
struct Fixture_complex_diamond {
    ///////////////////////////////////////////////////////////
    // type aliases
    ///////////////////////////////////////////////////////////
    using Point = DGtal::Z3i::Point;
    using Domain = DGtal::Z3i::Domain;
    using KSpace = DGtal::Z3i::KSpace;

    using FixtureDigitalTopology = DGtal::Z3i::DT26_6;
    using FixtureDigitalSet = DGtal::DigitalSetByAssociativeContainer<
        DGtal::Z3i::Domain,
        std::unordered_set<typename DGtal::Z3i::Domain::Point>>;
    using FixtureObject =
        DGtal::Object<FixtureDigitalTopology, FixtureDigitalSet>;
    using FixtureComplex = DGtal::VoxelComplex<KSpace, FixtureObject>;

    ///////////////////////////////////////////////////////////
    // fixture data
    FixtureObject obj_fixture;
    FixtureComplex complex_fixture;
    KSpace ks_fixture; // needed because ConstAlias in CC constructor.
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////
    Fixture_complex_diamond() : complex_fixture(ks_fixture) {
        create_complex_from_object(create_object());
    }

    ///////////////////////////////////////////////////////////
    // Function members
    ///////////////////////////////////////////////////////////
    FixtureObject &create_object() {
        using namespace DGtal;

        // trace.beginBlock ( "Create Fixture_object_diamond" );
        Point p1(-10, -10, -10);
        Point p2(10, 10, 10);
        Domain domain(p1, p2);
        Point c(0, 0, 0);

        // diamond of radius 4
        FixtureDigitalSet diamond_set(domain);
        for (auto it = domain.begin(); it != domain.end(); ++it) {
            if ((*it - c).norm1() <= 3)
                diamond_set.insertNew(*it);
        }
        diamond_set.erase(c);

        FixtureDigitalTopology::ForegroundAdjacency adjF;
        FixtureDigitalTopology::BackgroundAdjacency adjB;
        FixtureDigitalTopology topo(
            adjF, adjB, DGtal::DigitalTopologyProperties::JORDAN_DT);
        return obj_fixture = FixtureObject(topo, diamond_set);
    }

    FixtureComplex &create_complex_from_object(FixtureObject &input_obj) {

        ks_fixture.init(input_obj.domain().lowerBound(),
                        input_obj.domain().upperBound(), true);
        complex_fixture = FixtureComplex(ks_fixture);
        complex_fixture.construct(input_obj);
        return complex_fixture;
    }
};

TEST_CASE_METHOD(Fixture_complex_diamond, "insertVoxel", "[insert][close]") {
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    auto s3 = vc.nbCells(3);
    auto s2 = vc.nbCells(2);
    auto s1 = vc.nbCells(1);
    auto s0 = vc.nbCells(0);
    SECTION("insertVoxel in border") {
        Point p{0, 0, 4};
        auto vc_new = vc;
        vc_new.insertVoxelPoint(p);
        auto sa3 = vc_new.nbCells(3);
        auto sa2 = vc_new.nbCells(2);
        auto sa1 = vc_new.nbCells(1);
        auto sa0 = vc_new.nbCells(0);
        auto d3 = sa3 - s3;
        CHECK(d3 == 1);
        auto d2 = sa2 - s2;
        CHECK(d2 == 5);
        auto d1 = sa1 - s1;
        CHECK(d1 == 8);
        auto d0 = sa0 - s0;
        CHECK(d0 == 4);
    }
    SECTION("insertVoxel isolated") {
        Point p{5, 0, 0};
        auto vc_new = vc;
        vc_new.insertVoxelCell(ks.uSpel(p));
        auto sa3 = vc_new.nbCells(3);
        auto sa2 = vc_new.nbCells(2);
        auto sa1 = vc_new.nbCells(1);
        auto sa0 = vc_new.nbCells(0);
        auto d3 = sa3 - s3;
        CHECK(d3 == 1);
        auto d2 = sa2 - s2;
        CHECK(d2 == 6);
        auto d1 = sa1 - s1;
        CHECK(d1 == 12);
        auto d0 = sa0 - s0;
        CHECK(d0 == 8);
    }
    SECTION("insertVoxel interior") {
        Point p{0, 2, 0};
        auto vc_new = vc;
        vc_new.insertVoxelCell(ks.uSpel(p));
        auto sa3 = vc_new.nbCells(3);
        auto sa2 = vc_new.nbCells(2);
        auto sa1 = vc_new.nbCells(1);
        auto sa0 = vc_new.nbCells(0);
        auto d3 = sa3 - s3;
        CHECK(d3 == 0);
        auto d2 = sa2 - s2;
        CHECK(d2 == 0);
        auto d1 = sa1 - s1;
        CHECK(d1 == 0);
        auto d0 = sa0 - s0;
        CHECK(d0 == 0);
    }
}

TEST_CASE_METHOD(Fixture_complex_diamond, "Faces of voxel",
                 "[neighborhood][faces]") {
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    bool closed = true;
    bool no_hint = false;
    auto not_found = vc.end(3);

    SECTION("Voxel is in the interior of the complex.") {
        Point p{0, 0, 2};
        auto cellMapIt = vc.findCell(3, ks.uSpel(p));
        CHECK(cellMapIt != not_found);
        auto cell = cellMapIt->first;
        auto kfaces = ks.uFaces(cell);
        CAPTURE(p);
        CAPTURE(cell);
        CHECK(kfaces.size() == 26);
        auto vcBoundary_closed = vc.cellBoundary(cell, closed);
        CHECK(vcBoundary_closed.size() == 26);
        auto vcBoundary_no_hint = vc.cellBoundary(cell, no_hint);
        CHECK(vcBoundary_no_hint.size() == 26);
    }
    SECTION("Voxel is in the exterior") {
        Point p{0, 0, 5};
        auto cellMapIt = vc.findCell(3, ks.uSpel(p));
        CHECK(cellMapIt == not_found);
        auto cell = ks.uSpel(p);
        auto kfaces = ks.uFaces(cell);
        CAPTURE(p);
        CAPTURE(cell);
        CHECK(kfaces.size() == 26);
        // We know that is not closed, but checking the differences:
        auto vcBoundary_closed = vc.cellBoundary(cell, closed);
        CHECK(vcBoundary_closed.size() == 26);
        // Right method to call:
        auto vcBoundary_no_hint = vc.cellBoundary(cell, no_hint);
        CHECK(vcBoundary_no_hint.size() == 0);
    }
    SECTION("Voxel is out, but surrounded by in voxels") {
        Point p{0, 0, 0};
        auto cellMapIt = vc.findCell(3, ks.uSpel(p));
        CHECK(cellMapIt == not_found);
        auto cell = ks.uSpel(p);
        auto kfaces = ks.uFaces(cell);
        CAPTURE(p);
        CAPTURE(cell);
        CHECK(kfaces.size() == 26);
        auto vcBoundary_closed = vc.cellBoundary(cell, closed);
        CHECK(vcBoundary_closed.size() == 26);
        auto vcBoundary_no_hint = vc.cellBoundary(cell, no_hint);
        CHECK(vcBoundary_no_hint.size() == 26);
    }
    SECTION("Voxel is in the border") {
        Point p{0, 0, 3};
        auto cellMapIt = vc.findCell(3, ks.uSpel(p));
        CHECK(cellMapIt != not_found);
        auto cell = cellMapIt->first;
        auto kfaces = ks.uFaces(cell);
        CAPTURE(p);
        CAPTURE(cell);
        CHECK(kfaces.size() == 26);
        auto vcBoundary_closed = vc.cellBoundary(cell, closed);
        CHECK(vcBoundary_closed.size() == 26);
        auto vcBoundary_no_hint = vc.cellBoundary(cell, no_hint);
        CHECK(vcBoundary_no_hint.size() == 26);
    }
}

TEST_CASE_METHOD(Fixture_complex_diamond, "Neighbors from Object and KSpace",
                 "[neighborhood]") {
    auto &vc = complex_fixture;
    SECTION(" comparing neighbors from Kspace and from Object") {
        {
            size_t dim_voxel = 3;
            auto it = vc.begin(dim_voxel);
            for (auto &&n : std::vector<int>(10))
                ++it;
            auto cell = it->first;
            auto point_from_objectSet_1 = vc.objPointFromVoxel(cell);
            auto point_from_kspace_1 = cell.preCell().coordinates;
            SECTION(
                " points from Kspace and digital set have different coords ") {
                // point coordinates are different in the Kspace and in
                // DigitalSet.
                CHECK(point_from_objectSet_1 != point_from_kspace_1);
                SECTION("But uCoords from KSpace gives same coords than the "
                        "object set") {
                    CHECK(vc.space().uCoords(cell) == point_from_objectSet_1);
                    CHECK(vc.space().uKCoords(cell) == point_from_kspace_1);
                }
            }

            SECTION("properNeighborhood from Object with full topology"
                    "outputs all adjacent voxels") {
                auto neigh_obj =
                    vc.object().neighborhood(point_from_objectSet_1);
                CHECK(neigh_obj.size() == 12);
                auto propN_obj =
                    vc.object().properNeighborhood(point_from_objectSet_1);
                CHECK(propN_obj.size() == 11);

                SECTION("properNeighborhood from KSpace"
                        "does not output all adjacent voxels.") {

                    auto neigh_k = vc.space().uNeighborhood(cell);
                    CHECK(neigh_k.size() != neigh_obj.size());

                    auto propN_k = vc.space().uProperNeighborhood(cell);
                    CHECK(propN_k.size() != propN_obj.size());
                }
            }

            SECTION("Getting associated pointels and voxels from input_cell") {
                std::set<FixtureComplex::Cell> pointel_set;
                vc.pointelsFromCell(pointel_set, cell);
                std::set<FixtureComplex::Cell> voxel_set;
                for (auto &&p : pointel_set)
                    vc.spelsFromCell(voxel_set, p);
                SECTION("Gets desired full adjancency for voxels") {
                    CHECK(voxel_set.size() == 12);
                }
                auto clique = vc.Kneighborhood(cell);
                CHECK(clique.nbCells(3) == 12);
            }
        }
    }
}

TEST_CASE_METHOD(Fixture_complex_diamond, "Test Object Wrappers", "[object]") {
    auto &vc = complex_fixture;
    size_t dim_voxel = 3;
    auto cit = vc.begin(dim_voxel);
    for (auto &&n : std::vector<int>(10))
        ++cit;
    auto cell = cit->first;

    SECTION("querying voxel simplicity") {
        size_t nsimples{0};
        std::vector<FixtureComplex::Cell> non_simple_cells;
        for (auto it = vc.begin(dim_voxel); it != vc.end(dim_voxel); ++it) {
            if (vc.isSimple(it->first))
                ++nsimples;
            else
                non_simple_cells.emplace_back(it->first);
        }

        // Border points are simple in diamond.
        auto border_size = vc.object().border().size();
        REQUIRE(nsimples == border_size);
    }

    SECTION("querying object connectivity") {
        REQUIRE(vc.isConnected() == true);
    }
}

TEST_CASE_METHOD(Fixture_complex_diamond, "connectedComponents",
                 "[object][functions][components]") {
    auto &vc = complex_fixture;
    SECTION("getting connected components") {
        auto obj_components = functions::connectedComponents(vc.object(), true);
        REQUIRE(obj_components.size() == 1);
    }
}

TEST_CASE_METHOD(Fixture_complex_diamond, "Test table wrappers",
                 "[table][simple]") {
    auto &vc = complex_fixture;
    trace.beginBlock("loadTable");
    vc.setSimplicityTable(functions::loadTable(simplicity::tableSimple26_6));
    trace.endBlock();
    size_t dim_voxel = 3;
    auto cit = vc.begin(dim_voxel);
    for (auto &&n : std::vector<int>(10))
        ++cit;
    auto cell = cit->first;

    SECTION("querying voxel simplicity") {
        size_t nsimples{0};
        std::vector<FixtureComplex::Cell> non_simple_cells;
        for (auto it = vc.begin(dim_voxel); it != vc.end(dim_voxel); ++it) {
            if (vc.isSimple(it->first))
                ++nsimples;
            else
                non_simple_cells.emplace_back(it->first);
        }

        // Border points are simple in diamond.
        auto border_size = vc.object().border().size();
        REQUIRE(nsimples == border_size);
    }
}

TEST_CASE_METHOD(Fixture_complex_diamond, "Cliques Masks K_2", "[clique]") {
    auto &vc = complex_fixture;
    auto itc = vc.begin(3);
    for (auto &&n : std::vector<int>(10))
        ++itc;
    auto cell = itc->first;
    Point p_cell = vc.space().uCoords(cell);

    auto voxel_point = vc.objPointFromVoxel(cell);
    auto neigh6 = vc.object().geodesicNeighborhood(
        DGtal::Z3i::adj6, voxel_point, sqrt(2.0) / 2.0);
    REQUIRE(neigh6.size() == 2); // It is a corner
    std::vector<std::pair<bool, FixtureComplex::Clique>> cliques_p;
    bool verbose = true;
    for (auto &&n : neigh6.pointSet()) {
        cliques_p.emplace_back(vc.K_2(p_cell, n, verbose));
        auto &is_critical = cliques_p.back().first;
        auto &k2_clique = cliques_p.back().second;
        CHECK(is_critical == true);
        CHECK(k2_clique.nbCells(3) == 2);
    }
    SECTION(" Check same results for different K_2 interfaces") {
        for (auto &&n : neigh6.pointSet()) {
            auto cell_n = vc.space().uSpel(n);
            auto co_face = vc.surfelBetweenAdjacentSpels(cell_n, cell);

            using namespace DGtal::functions;
            CHECK(isEqual(vc.K_2(p_cell, n, false).second,
                          vc.K_2(cell, cell_n, false).second) == true);
            CHECK(isEqual(vc.K_2(p_cell, n, false).second,
                          vc.K_2(co_face, false).second) == true);
        } // endfor
    }     // then_interfaces
} // test

TEST_CASE_METHOD(Fixture_complex_diamond, "Cliques Masks K_1", "[clique]") {
    auto &vc = complex_fixture;
    auto itc = vc.begin(3);
    for (auto &&n : std::vector<int>(10))
        ++itc;
    auto cell = itc->first;
    Point p_cell = vc.space().uCoords(cell);

    auto voxel_point = vc.objPointFromVoxel(cell);
    auto neigh6 = vc.object().geodesicNeighborhood(
        DGtal::Z3i::adj6, voxel_point, sqrt(2.0) / 2.0);
    REQUIRE(neigh6.size() == 2); // It is a corner
    SECTION("K_1 mask from a linel") {
        auto linel =
            vc.space().uCell(cell.preCell().coordinates + Point{0, 1, 1});

        using namespace DGtal::functions;
        auto k1p = vc.K_1(linel, true);
        auto &is_critical = k1p.first;
        CHECK(is_critical == true);
        auto &k1_clique = k1p.second;
        // numer of voxels in clique
        CHECK(k1_clique.nbCells(3) == 3);
    }
} // test

TEST_CASE_METHOD(Fixture_complex_diamond, "Cliques Masks K_0", "[clique]") {
    auto &vc = complex_fixture;
    auto itc = vc.begin(3);
    for (auto &&n : std::vector<int>(10))
        ++itc;
    auto cell = itc->first;
    Point p_cell = vc.space().uCoords(cell);

    auto voxel_point = vc.objPointFromVoxel(cell);
    auto neigh6 = vc.object().geodesicNeighborhood(
        DGtal::Z3i::adj6, voxel_point, sqrt(2.0) / 2.0);
    REQUIRE(neigh6.size() == 2); // It is a corner
    SECTION("K_0 mask from a pointel") {
        auto pointel = vc.space().uPointel(p_cell);
        // auto pointel = vc.space().uPointel(Point{0,0,0});

        using namespace DGtal::functions;
        auto k0_mask = vc.K_0(pointel, true);

        auto &is_critical = k0_mask.first;
        CHECK(is_critical == false);
        auto &k0_clique = k0_mask.second;
        // numer of voxels in clique
        CHECK(k0_clique.nbCells(3) == 1);
    }
} // test

TEST_CASE_METHOD(Fixture_complex_diamond, "Get All Critical Cliques of diamond",
                 "[critical][clique]") {
    auto &vc = complex_fixture;
    using namespace DGtal::functions;
    SECTION(" Get all criticalCliques() ") {
        auto criticals = vc.criticalCliques();
        CHECK(criticals.size() == 4);

        CHECK(vc.nbCells(3) == 62);
        CHECK(criticals[3].size() == 18);
        CHECK(vc.nbCells(2) == 264);
        CHECK(criticals[2].size() == 108);
        CHECK(vc.nbCells(1) == 360);
        CHECK(criticals[1].size() == 168);
        CHECK(vc.nbCells(0) == 160);
        CHECK(criticals[0].size() == 32);
    }
}

///////////////////////////////////////////////////////////////////////////
// Fixture for complex fig 4 of Asymmetric parallel 3D thinning scheme
///////////////////////////////////////////////////////////////////////////
struct Fixture_complex_fig4 {
    ///////////////////////////////////////////////////////////
    // type aliases
    ///////////////////////////////////////////////////////////
    using Point = DGtal::Z3i::Point;
    using Domain = DGtal::Z3i::Domain;
    using KSpace = DGtal::Z3i::KSpace;

    using FixtureDigitalTopology = DGtal::Z3i::DT26_6;
    using FixtureDigitalSet = DGtal::DigitalSetByAssociativeContainer<
        DGtal::Z3i::Domain,
        std::unordered_set<typename DGtal::Z3i::Domain::Point>>;
    using FixtureObject =
        DGtal::Object<FixtureDigitalTopology, FixtureDigitalSet>;
    using FixtureMap = std::unordered_map<KSpace::Cell, CubicalCellData>;
    using FixtureComplex =
        DGtal::VoxelComplex<KSpace, FixtureObject, FixtureMap>;

    ///////////////////////////////////////////////////////////
    // fixture data
    FixtureObject obj_fixture;
    FixtureComplex complex_fixture;
    KSpace ks_fixture; // needed because ConstAlias in CC constructor.
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////
    Fixture_complex_fig4() : complex_fixture(ks_fixture) {
        create_complex_from_object(create_object());
    }

    ///////////////////////////////////////////////////////////
    // Function members
    ///////////////////////////////////////////////////////////
    FixtureObject &create_object() {
        using namespace DGtal;

        Point p1(-10, -10, -10);
        Point p2(10, 10, 10);
        Domain domain(p1, p2);

        // 12 voxels of fig4, centered in critical voxel
        FixtureDigitalSet fig4_set(domain);
        Point a1(0, 0, 0);
        fig4_set.insertNew(a1);
        Point a2(0, -1, 0);
        fig4_set.insertNew(a2);
        Point a3(1, -1, 0);
        fig4_set.insertNew(a3);
        Point c1(0, 1, -1);
        fig4_set.insertNew(c1);
        Point c2(1, 1, -1);
        fig4_set.insertNew(c2);
        Point c3(1, 2, -1);
        fig4_set.insertNew(c3);
        Point c4(0, 2, -1);
        fig4_set.insertNew(c4);
        Point b1(0, 2, 0);
        fig4_set.insertNew(b1);
        Point b2(-1, 3, 0);
        fig4_set.insertNew(b2);
        Point l1(1, 0, -2);
        fig4_set.insertNew(l1);
        Point l2(2, 0, -2);
        fig4_set.insertNew(l2);
        Point r1(1, 3, -2);
        fig4_set.insertNew(r1);

        FixtureDigitalTopology::ForegroundAdjacency adjF;
        FixtureDigitalTopology::BackgroundAdjacency adjB;
        FixtureDigitalTopology topo(
            adjF, adjB, DGtal::DigitalTopologyProperties::JORDAN_DT);
        return obj_fixture = FixtureObject(topo, fig4_set);
    }

    FixtureComplex &create_complex_from_object(FixtureObject &input_obj) {

        ks_fixture.init(input_obj.domain().lowerBound(),
                        input_obj.domain().upperBound(), true);
        complex_fixture = FixtureComplex(ks_fixture);
        complex_fixture.construct(input_obj);
        return complex_fixture;
    }
};
TEST_CASE_METHOD(Fixture_complex_fig4, "Get All Critical Cliques of fig4",
                 "[critical][clique]") {
    auto &vc = complex_fixture;
    using namespace DGtal::functions;
    SECTION(" Get all criticalCliques() ") {
        auto criticals = vc.criticalCliques(true);
        CHECK(criticals.size() == 4);

        CHECK(vc.nbCells(3) == 12);
        CHECK(criticals[3].size() == 1);
        CHECK(vc.nbCells(2) == 64);
        CHECK(criticals[2].size() == 3);
        CHECK(vc.nbCells(1) == 109);
        CHECK(criticals[1].size() == 2);
        CHECK(vc.nbCells(0) == 58);
        CHECK(criticals[0].size() == 6);
    }
}
TEST_CASE_METHOD(Fixture_complex_fig4, "zeroSurface and oneSurface",
                 "[isSurface][function]") {
    auto &vc = complex_fixture;
    using namespace DGtal::functions;
    using Point = FixtureComplex::Point;
    vc.clear();
    vc.objectSet().clear();
    Point c(0, 0, 0);
    {
        vc.objectSet().insertNew(c);
        vc.insertCell(3, vc.space().uSpel(c));
    }
    Point r(0, 1, 0);
    {
        vc.objectSet().insertNew(r);
        vc.insertCell(3, vc.space().uSpel(r));
    }
    Point l(0, -1, 0);
    {
        vc.objectSet().insertNew(l);
        vc.insertCell(3, vc.space().uSpel(l));
    }
    SECTION("checking zero surfaces of original set") {
        std::set<Point> zeroSurfacesCells;
        for (const auto &p : vc.objectSet()) {
            auto small_obj = vc.object().properNeighborhood(p);
            if (isZeroSurface(small_obj))
                zeroSurfacesCells.insert(p);
        }
        CHECK(zeroSurfacesCells.size() == 1);
    }
    SECTION("checking one surfaces of original set") {
        Point u(-1, 0, 0);
        {
            vc.objectSet().insertNew(u);
            vc.insertCell(3, vc.space().uSpel(u));
        }
        Point d(1, 0, 0);
        {
            vc.objectSet().insertNew(d);
            vc.insertCell(3, vc.space().uSpel(d));
        }
        std::set<Point> oneSurfacesCells;
        for (const auto &p : vc.objectSet()) {
            auto small_obj = vc.object().properNeighborhood(p);
            if (isOneSurface(small_obj))
                oneSurfacesCells.insert(p);
        }
        CHECK(oneSurfacesCells.size() == 1);
    }
}

///////////////////////////////////////////////////////////////////////////
// Fixture for complex fig 4 of Asymmetric parallel 3D thinning scheme
///////////////////////////////////////////////////////////////////////////
struct Fixture_isthmus {
    ///////////////////////////////////////////////////////////
    // type aliases
    ///////////////////////////////////////////////////////////
    using Point = DGtal::Z3i::Point;
    using Domain = DGtal::Z3i::Domain;
    using KSpace = DGtal::Z3i::KSpace;

    using FixtureDigitalTopology = DGtal::Z3i::DT26_6;
    using FixtureDigitalSet = DGtal::DigitalSetByAssociativeContainer<
        DGtal::Z3i::Domain,
        std::unordered_set<typename DGtal::Z3i::Domain::Point>>;
    using FixtureObject =
        DGtal::Object<FixtureDigitalTopology, FixtureDigitalSet>;
    using FixtureMap = std::unordered_map<KSpace::Cell, CubicalCellData>;
    using FixtureComplex =
        DGtal::VoxelComplex<KSpace, FixtureObject, FixtureMap>;

    ///////////////////////////////////////////////////////////
    // fixture data
    FixtureObject obj_fixture;
    FixtureComplex complex_fixture;
    KSpace ks_fixture; // needed because ConstAlias in CC constructor.
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////
    Fixture_isthmus() : complex_fixture(ks_fixture) {
        create_complex_from_object(create_object());
    }

    ///////////////////////////////////////////////////////////
    // Function members
    ///////////////////////////////////////////////////////////
    FixtureObject &create_object() {
        using namespace DGtal;

        Point p1(-10, -10, -10);
        Point p2(10, 10, 10);
        Domain domain(p1, p2);

        FixtureDigitalSet fig6_set(domain);

        Point c00(0, 0, 0);
        fig6_set.insertNew(c00);
        Point c01(-1, 0, 0);
        fig6_set.insertNew(c01);
        Point c02(-2, 0, 0);
        fig6_set.insertNew(c02);
        Point c03(-2, 0, 1);
        fig6_set.insertNew(c03);

        Point c10(0, 1, 0);
        fig6_set.insertNew(c10);
        Point y(-1, 1, 0);
        fig6_set.insertNew(y);
        Point c12(-2, 1, 0);
        fig6_set.insertNew(c12);
        Point c13(-2, 1, 1);
        fig6_set.insertNew(c13);

        Point c20(0, 2, 0);
        fig6_set.insertNew(c20);
        Point c21(-1, 2, 0);
        fig6_set.insertNew(c21);
        Point c22(-1, 2, 1);
        fig6_set.insertNew(c22);
        Point c33(-1, 2, -1);
        fig6_set.insertNew(c33);

        Point c30(-1, 3, 0);
        fig6_set.insertNew(c30);
        Point c31(-1, 3, 1);
        fig6_set.insertNew(c31);

        Point x(-1, 4, 0);
        fig6_set.insertNew(x);

        Point c50(-1, 5, 0);
        fig6_set.insertNew(c50);
        Point c51(-1, 5, -1);
        fig6_set.insertNew(c51);
        Point c52(-2, 5, 0);
        fig6_set.insertNew(c52);

        Point c60(-1, 6, 0);
        fig6_set.insertNew(c60);
        Point c61(-2, 6, 0);
        fig6_set.insertNew(c61);
        Point c62(-2, 6, -1);
        fig6_set.insertNew(c62);

        FixtureDigitalTopology::ForegroundAdjacency adjF;
        FixtureDigitalTopology::BackgroundAdjacency adjB;
        FixtureDigitalTopology topo(
            adjF, adjB, DGtal::DigitalTopologyProperties::JORDAN_DT);
        return obj_fixture = FixtureObject(topo, fig6_set);
    }

    FixtureComplex &create_complex_from_object(FixtureObject &input_obj) {

        ks_fixture.init(input_obj.domain().lowerBound(),
                        input_obj.domain().upperBound(), true);
        complex_fixture = FixtureComplex(ks_fixture);
        complex_fixture.construct(input_obj);
        return complex_fixture;
    }
};

TEST_CASE_METHOD(Fixture_isthmus, "Thin disconnected complex",
                 "[isthmus][thin][function]") {
    using namespace DGtal::functions;
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    // Delete one point and reconstruct complex.
    Point x(-1, 4, 0);
    obj_fixture.pointSet().erase(x);
    vc.clear();
    vc.construct(obj_fixture);
    SECTION("with skelUltimate") {
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectFirst<FixtureComplex>, skelUltimate<FixtureComplex>);
        CHECK(vc_new.nbCells(3) == 2);
    }
}
TEST_CASE_METHOD(Fixture_isthmus, "Check isthmus", "[isthmus][function]") {
    auto &vc = complex_fixture;
    using namespace DGtal::functions;
    auto &ks = vc.space();
    Point x(-1, 4, 0); // oneIsthmus
    Point y(-1, 1, 0); // twoIsthmus

    SECTION("checking one isthmus") {
        std::set<Point> isthmus;
        for (const auto &p : vc.objectSet()) {
            if (oneIsthmus(vc, ks.uSpel(p)))
                isthmus.insert(p);
        }
        CHECK(isthmus.size() == 1);
        auto xit = isthmus.find(x);
        CHECK(*xit == x);
    }

    SECTION("checking 2 isthmus") {
        std::set<Point> isthmus;
        for (const auto &p : vc.objectSet()) {
            if (twoIsthmus(vc, ks.uSpel(p)))
                isthmus.insert(p);
        }
        CHECK(isthmus.size() == 1);
        auto yit = isthmus.find(y);
        CHECK(*yit == y);
    }

    SECTION("checking 1 and 2 isthmus") {
        std::set<Point> isthmus;
        for (const auto &p : vc.objectSet()) {
            if (skelIsthmus(vc, ks.uSpel(p)))
                isthmus.insert(p);
        }
        CHECK(isthmus.size() == 2);
        auto xit = isthmus.find(x);
        auto yit = isthmus.find(y);
        CHECK(xit != isthmus.end());
        CHECK(yit != isthmus.end());
    }
}

TEST_CASE_METHOD(Fixture_isthmus, "Thin complex", "[isthmus][thin][function]") {
    using namespace DGtal::functions;
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    SECTION("with skelUltimate") {
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectFirst<FixtureComplex>, skelUltimate<FixtureComplex>);
        CHECK(vc_new.nbCells(3) == 1);
    }
    SECTION("with skelEnd") {
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectFirst<FixtureComplex>, skelEnd<FixtureComplex>);
        CHECK(vc_new.nbCells(3) == 5);
    }
    SECTION("with oneIsthmus") {
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, oneIsthmus<FixtureComplex>);
        CHECK(vc_new.nbCells(3) == 3);
    }
    SECTION("with twoIsthmus") {
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, twoIsthmus<FixtureComplex>);
        CHECK(vc_new.nbCells(3) == 1);
    }
    SECTION("with skelIsthmus") {
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelIsthmus<FixtureComplex>);
        CHECK(vc_new.nbCells(3) == 3);
    }
}
//
TEST_CASE_METHOD(Fixture_isthmus, "Persistence thin",
                 "[persistence][isthmus][thin][function]") {
    using namespace DGtal::functions;
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    SECTION("with skelUltimate") {
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelUltimate<FixtureComplex>, 0);
        CHECK(vc_new.nbCells(3) == 1);
    }
    SECTION("with skelEnd") {
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelEnd<FixtureComplex>, 0);
        CHECK(vc_new.nbCells(3) == 5);
    }
    SECTION("with oneIsthmus") {
        /* Not using LUT skel function (slow):
        auto vc_new = persistenceAsymetricThinningScheme< FixtureComplex >(
            vc, selectRandom<FixtureComplex>, oneIsthmus<FixtureComplex>, 0);
        */
        // with LUT:
        auto table = *functions::loadTable(isthmusicity::tableOneIsthmus);
        auto pointToMaskMap =
            *functions::mapZeroPointNeighborhoodToConfigurationMask<
                FixtureObject::Point>();
        auto oneIsthmusTable =
            [&table, &pointToMaskMap](const FixtureComplex &fc,
                                      const FixtureComplex::Cell &c) {
                return skelWithTable(table, pointToMaskMap, fc, c);
            };
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, oneIsthmusTable, 0);
        CHECK(vc_new.nbCells(3) == 3);
    }
    SECTION("with twoIsthmus") {
        /* Not using LUT skel function (slow):
        auto vc_new = persistenceAsymetricThinningScheme< FixtureComplex >(
            vc, selectRandom<FixtureComplex>, twoIsthmus<FixtureComplex>, 0);
        */
        // with LUT:
        auto table = *functions::loadTable(isthmusicity::tableTwoIsthmus);
        auto pointToMaskMap =
            *functions::mapZeroPointNeighborhoodToConfigurationMask<
                FixtureObject::Point>();
        auto twoIsthmusTable =
            [&table, &pointToMaskMap](const FixtureComplex &fc,
                                      const FixtureComplex::Cell &c) {
                return skelWithTable(table, pointToMaskMap, fc, c);
            };
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, twoIsthmusTable, 0);
        CHECK(vc_new.nbCells(3) == 1);
    }
    SECTION("with skelIsthmus") {
        /* Not using LUT skel function (slow):
        auto vc_new = persistenceAsymetricThinningScheme< FixtureComplex >(
            vc, selectRandom<FixtureComplex>, skelIsthmus<FixtureComplex>, 0);
        */
        // with LUT:
        auto table = *functions::loadTable(isthmusicity::tableIsthmus);
        auto pointToMaskMap =
            *functions::mapZeroPointNeighborhoodToConfigurationMask<
                FixtureObject::Point>();
        auto isthmusTable = [&table,
                             &pointToMaskMap](const FixtureComplex &fc,
                                              const FixtureComplex::Cell &c) {
            return skelWithTable(table, pointToMaskMap, fc, c);
        };
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, isthmusTable, 0);
        CHECK(vc_new.nbCells(3) == 3);
        // SECTION( "visualize the thining" ){
        //   int argc(1);
        //   char** argv(nullptr);
        //   QApplication app(argc, argv);
        //   Viewer3D<> viewer(ks_fixture);
        //   viewer.show();
        //
        //   viewer.setFillColor(Color(200, 200, 200, 100));
        //   for ( auto it = vc_new.begin(3); it!= vc_new.end(3); ++it )
        //     viewer << it->first;
        //
        //   viewer.setFillColor(Color(200, 200, 200, 100));
        //   // All kspace voxels
        //   viewer.setFillColor(Color(40, 200, 55, 30));
        //   for ( auto it = vc.begin(3); it!= vc.end(3); ++it )
        //     viewer << it->first;
        //
        //   viewer << Viewer3D<>::updateDisplay;
        //   app.exec();
        // }
    }
}

///////////////////////////////////////////////////////////////////////////
// Fixture for a thick X
struct Fixture_X {
    ///////////////////////////////////////////////////////////
    // type aliases
    ///////////////////////////////////////////////////////////
    using Point = DGtal::Z3i::Point;
    using Domain = DGtal::Z3i::Domain;
    using KSpace = DGtal::Z3i::KSpace;

    using FixtureDigitalTopology = DGtal::Z3i::DT26_6;
    using FixtureDigitalSet = DGtal::DigitalSetByAssociativeContainer<
        DGtal::Z3i::Domain,
        std::unordered_set<typename DGtal::Z3i::Domain::Point>>;
    using FixtureObject =
        DGtal::Object<FixtureDigitalTopology, FixtureDigitalSet>;
    using FixtureMap = std::unordered_map<KSpace::Cell, CubicalCellData>;
    using FixtureComplex =
        DGtal::VoxelComplex<KSpace, FixtureObject>;

    ///////////////////////////////////////////////////////////
    // fixture data
    FixtureObject obj_fixture;
    FixtureComplex complex_fixture;
    KSpace ks_fixture; // needed because ConstAlias in CC constructor.
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////
    Fixture_X() : complex_fixture(ks_fixture) {
        create_complex_from_object(create_object());
    }

    ///////////////////////////////////////////////////////////
    // Function members
    ///////////////////////////////////////////////////////////
    FixtureObject &create_object() {
        using namespace DGtal;

        Point p1(-30, -30, -30);
        Point p2(30, 30, 30);
        Domain domain(p1, p2);

        FixtureDigitalSet a_set(domain);
        std::vector<Point> center_set;
        center_set.reserve(9);

        Point c00(0, 0, 0);
        center_set.push_back(c00);
        Point c01x(-1, 0, 0);
        center_set.push_back(c01x);
        Point c10x(1, 0, 0);
        center_set.push_back(c10x);
        Point c02x(-2, 0, 0);
        center_set.push_back(c02x);
        Point c20x(2, 0, 0);
        center_set.push_back(c20x);

        Point c01y(0, -1, 0);
        center_set.push_back(c01y);
        Point c10y(0, 1, 0);
        center_set.push_back(c10y);
        Point c02y(0, -2, 0);
        center_set.push_back(c02y);
        Point c20y(0, 2, 0);
        center_set.push_back(c20y);

        Point z_pos(0, 0, 1);
        int branch_length(10);
        std::vector<Point> diagonals;
        diagonals.reserve(6);
        for (const auto &p : center_set) {
            diagonals.clear();
            for (int l = 0; l <= branch_length; ++l) {
                diagonals.push_back({l, l, 0});
                diagonals.push_back({l, -l, 0});
                diagonals.push_back({-l, l, 0});
                diagonals.push_back({-l, -l, 0});
                for (int z = -2; z <= 2; ++z)
                    for (const auto &d : diagonals)
                        a_set.insert(p + d + (z * z_pos));
            }
        }

        FixtureDigitalTopology::ForegroundAdjacency adjF;
        FixtureDigitalTopology::BackgroundAdjacency adjB;
        FixtureDigitalTopology topo(
            adjF, adjB, DGtal::DigitalTopologyProperties::JORDAN_DT);
        return obj_fixture = FixtureObject(topo, a_set);
    }

    FixtureComplex &create_complex_from_object(FixtureObject &input_obj) {

        ks_fixture.init(input_obj.domain().lowerBound(),
                        input_obj.domain().upperBound(), true);
        complex_fixture = FixtureComplex(ks_fixture);
        complex_fixture.construct(input_obj);
        return complex_fixture;
    }
};
TEST_CASE_METHOD(Fixture_X, "X Thin",
                 "[x][persistence][isthmus][thin][function]") {
    using namespace DGtal::functions;
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    bool verbose = true;
    SECTION(
        "persistence value of 1 is equivalent to the assymetric algorithm") {
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectFirst<FixtureComplex>, skelEnd<FixtureComplex>, 1,
            verbose);

        auto vc_assymetric = asymetricThinningScheme<FixtureComplex>(
            vc, selectFirst<FixtureComplex>, skelEnd<FixtureComplex>, true);
        // 10% tolerance
        CHECK(vc_assymetric.nbCells(3) ==
              Approx(vc_new.nbCells(3)).epsilon(0.1));
    }
    SECTION("persistence value: infinite is equivalent to ultimate skeleton") {
        auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelEnd<FixtureComplex>, 100,
            verbose);
        REQUIRE(vc_new.nbCells(3) == 1);
    }
}

TEST_CASE_METHOD(Fixture_X, "X Thin with Isthmus, and tables",
                 "[x][isthmus][thin][function][table]") {
    using namespace DGtal::functions;
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    bool verbose = true;

    SECTION("Compute with skelIsthmus") {
        trace.beginBlock("skelIsthmus");
        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelIsthmus<FixtureComplex>,
            verbose);
        trace.endBlock();
    }
    SECTION("Compute with skelWithTable (isIsthmus)") {
        trace.beginBlock("skelIsthmus with table");
        auto table = *functions::loadTable(isthmusicity::tableIsthmus);
        auto pointToMaskMap =
            *functions::mapZeroPointNeighborhoodToConfigurationMask<
                FixtureObject::Point>();
        auto skelWithTableIsthmus =
            [&table, &pointToMaskMap](const FixtureComplex &fc,
                                      const FixtureComplex::Cell &c) {
                return skelWithTable(table, pointToMaskMap, fc, c);
            };

        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelWithTableIsthmus, verbose);

        trace.endBlock();
    }

    SECTION("Compute with skelWithTable (isIsthmus) and empty Object") {
        trace.beginBlock("skelIsthmus with table (empty objectSet)");
        vc.setSimplicityTable(
            functions::loadTable(simplicity::tableSimple26_6));
        vc.objectSet().clear();
        auto table = *functions::loadTable(isthmusicity::tableIsthmus);
        auto pointToMaskMap =
            *functions::mapZeroPointNeighborhoodToConfigurationMask<
                FixtureObject::Point>();
        auto skelWithTableIsthmus =
            [&table, &pointToMaskMap](const FixtureComplex &fc,
                                      const FixtureComplex::Cell &c) {
                return skelWithTable(table, pointToMaskMap, fc, c);
            };

        auto vc_new = asymetricThinningScheme<FixtureComplex>(
            vc, selectRandom<FixtureComplex>, skelWithTableIsthmus, verbose);

        trace.endBlock();
    }
}

/// Use distance map in the Select function.
TEST_CASE_METHOD(Fixture_X, "X DistanceMap", "[x][distance][thin]") {
    using namespace DGtal::functions;
    auto &vc = complex_fixture;
    auto &ks = vc.space();
    auto &obj = vc.object();
    using Predicate = Z3i::DigitalSet;
    using L3Metric = ExactPredicateLpSeparableMetric<Z3i::Space, 3>;
    using DT = DistanceTransformation<Z3i::Space, Predicate, L3Metric>;
    bool verbose = true;
    SECTION("Distance Map") {
        trace.beginBlock("With a Distance Map");
        L3Metric l3;
        DT dt(obj.domain(), obj.pointSet(), l3);
        // Create wrap around selectMaxValue to use the thinning.
        auto selectDistMax = [&dt](const FixtureComplex::Clique &clique) {
            return selectMaxValue<DT, FixtureComplex>(dt, clique);
        };
        SECTION("asymetricThinning"){
            auto vc_new = asymetricThinningScheme<FixtureComplex>(
                    vc, selectDistMax, skelEnd<FixtureComplex>, verbose);
        }
        SECTION("persistenceThinning"){
            auto table = *functions::loadTable(isthmusicity::tableOneIsthmus);
            auto pointToMaskMap =
                *functions::mapZeroPointNeighborhoodToConfigurationMask<
                FixtureObject::Point>();
            auto oneIsthmusTable =
                [&table, &pointToMaskMap](const FixtureComplex &fc,
                        const FixtureComplex::Cell &c) {
                    return skelWithTable(table, pointToMaskMap, fc, c);
                };
            int persistence = 3;
            auto vc_new = persistenceAsymetricThinningScheme<FixtureComplex>(
                    vc, selectDistMax, oneIsthmusTable,
                    persistence, verbose);
            // SECTION( "visualize the thining" ){
            //     int argc(1);
            //     char** argv(nullptr);
            //     QApplication app(argc, argv);
            //     Viewer3D<> viewer(ks_fixture);
            //     viewer.show();
            //
            //     viewer.setFillColor(Color(200, 200, 200, 100));
            //     for ( auto it = vc_new.begin(3); it!= vc_new.end(3); ++it )
            //         viewer << it->first;
            //
            //     // All kspace voxels
            //     viewer.setFillColor(Color(40, 40, 40, 10));
            //     for ( auto it = vc.begin(3); it!= vc.end(3); ++it )
            //         viewer << it->first;
            //
            //     viewer << Viewer3D<>::updateDisplay;
            //     app.exec();
            // }
        }

    }

    trace.endBlock();
}

// REQUIRE(vc_new.nbCells(3) == 38);
///////////////////////////////////////////////////////////////////////////////
