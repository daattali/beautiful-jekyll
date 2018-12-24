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
 * @file StdDefs.cpp
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2016/01/19
 *
 * This file is part of the DGtal library.
 */

#include "DGtal/helpers/StdDefs.h"


//////////////////
/// Z2i Explicit instanciation
//////////////////
template class DGtal::SpaceND<2, DGtal::Z2i::Integer>;
template class DGtal::PointVector<2, DGtal::Z2i::Integer>;
template class DGtal::KhalimskySpaceND< 2, DGtal::Z2i::Integer > ;
template class DGtal::HyperRectDomain< DGtal::Z2i::Space > ; 
template class DGtal::MetricAdjacency< DGtal::Z2i::Space, 1> ;
template class DGtal::MetricAdjacency< DGtal::Z2i::Space, 2> ;
template class DGtal::DigitalTopology< DGtal::Z2i::Adj4, DGtal::Z2i::Adj8 > ;
template class DGtal::DigitalTopology< DGtal::Z2i::Adj8, DGtal::Z2i::Adj4 > ;
template class DGtal::DigitalSetByAssociativeContainer<DGtal::Z2i::Domain,
                                                       std::unordered_set< typename DGtal::Z2i::Domain::Point> >;
template class DGtal::GridCurve<DGtal::Z2i::K2> ;
template class DGtal::ExactPredicateLpSeparableMetric<DGtal::Z2i::Space,2> ;
template class DGtal::ExactPredicateLpSeparableMetric<DGtal::Z2i::Space,1> ;
template class DGtal::ExactPredicateLpPowerSeparableMetric<DGtal::Z2i::Space,2> ;
template class DGtal::ExactPredicateLpPowerSeparableMetric<DGtal::Z2i::Space,1> ;


//////////////////
/// Z3i Explicit instanciation
//////////////////
template class DGtal::SpaceND<3, DGtal::Z3i::Integer>;
template class DGtal::PointVector<3, DGtal::Z3i::Integer>;
template class DGtal::KhalimskySpaceND< 3, DGtal::Z3i::Integer > ;
template class DGtal::HyperRectDomain< DGtal::Z3i::Space > ; 
template class DGtal::MetricAdjacency< DGtal::Z3i::Space, 1> ;
template class DGtal::MetricAdjacency< DGtal::Z3i::Space, 2> ;
template class DGtal::MetricAdjacency< DGtal::Z3i::Space, 3> ;
template class DGtal::DigitalTopology< DGtal::Z3i::Adj6, DGtal::Z3i::Adj26 > ;
template class DGtal::DigitalTopology< DGtal::Z3i::Adj26, DGtal::Z3i::Adj6 > ;
template class DGtal::DigitalTopology< DGtal::Z3i::Adj18, DGtal::Z3i::Adj26 > ;
template class DGtal::DigitalTopology< DGtal::Z3i::Adj26, DGtal::Z3i::Adj18 > ;
template class DGtal::DigitalSetByAssociativeContainer<DGtal::Z3i::Domain,
                                                       std::unordered_set< typename DGtal::Z3i::Domain::Point> >;
template class DGtal::ExactPredicateLpSeparableMetric<DGtal::Z3i::Space,2> ;
template class DGtal::ExactPredicateLpSeparableMetric<DGtal::Z3i::Space,1> ;
template class DGtal::ExactPredicateLpPowerSeparableMetric<DGtal::Z3i::Space,2> ;
template class DGtal::ExactPredicateLpPowerSeparableMetric<DGtal::Z3i::Space,1> ;
