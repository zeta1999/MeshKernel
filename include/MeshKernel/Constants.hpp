//---- GPL ---------------------------------------------------------------------
//
// Copyright (C)  Stichting Deltares, 2011-2020.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 3.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// contact: delft3d.support@deltares.nl
// Stichting Deltares
// P.O. Box 177
// 2600 MH Delft, The Netherlands
//
// All indications and logos of, and references to, "Delft3D" and "Deltares"
// are registered trademarks of Stichting Deltares, and remain the property of
// Stichting Deltares. All rights reserved.
//
//------------------------------------------------------------------------------

#pragma once

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

namespace meshkernel
{
    // missing value
    const double innerOuterSeparator = -998.0; ///< Double value used to separate the inner part of a polygon from its outer part
    const double doubleMissingValue = -999.0;  ///< Double value used as missing value
    const int intMissingValue = -999;          ///< Integer value used as missing value

    // often used values
    const double squareRootOfThree = 1.73205080756887729352; ///< The result of sqrt(3)
    const double oneThird = 1 / 3.0;                         ///< The result of 1 / 3

    // geometric constants
    const double degrad_hp = M_PI / 180.0;                   ///< Conversion factor from degrees to radians(pi / 180)
    const double raddeg_hp = 180.0 / M_PI;                   ///< Conversion factor from radians to degrees(180 / pi)
    const double earth_radius = 6378137.0;                   ///< Earth radius(m)
    const double one_over_earth_radius = 1.0 / earth_radius; ///< One over earth_radius(m-1);
    const double absLatitudeAtPoles = 0.0001;                ///< Pole tolerance in degrees
    const double nearlyZero = 1e-16;                         ///< Used to determine if a length is zero

    // mesh constants
    const double minimumDeltaCoordinate = 1e-14;                               ///< Minimum delta coordinate
    const int maximumNumberOfEdgesPerNode = 12;                                ///< Maximum number of edges per node
    const int maximumNumberOfEdgesPerFace = 6;                                 ///< Maximum number of edges per face
    const int maximumNumberOfNodesPerFace = 8;                                 ///< Maximum number of nodes per face
    const int maximumNumberOfConnectedNodes = maximumNumberOfEdgesPerNode * 4; ///< Maximum number of connected nodes
    const double minimumCellArea = 1e-12;                                      ///< Minimum cell area
    const double weightCircumCenter = 1.0;                                     ///< Weight circum center
    const int numNodesQuads = 4;                                               ///< Number of nodes in a quadrilateral
    const int numNodesInTriangle = 3;                                          ///< Number of nodes in a triangle

    // orthogonalization
    const double minimumEdgeLength = 1e-4;                   ///< Minimum edge length
    const double curvilinearToOrthogonalRatio = 0.5;         ///< Ratio determining curvilinear-like(0.0) to pure(1.0) orthogonalization
    const double orthogonalizationToSmoothingFactor = 0.975; ///< Factor between grid smoothing and grid ortho resp (0.<=ATPF<=1.)

    // merging distance
    const double mergingDistance = 0.001;                                    ///< Merging distance
    const double mergingDistanceSquared = mergingDistance * mergingDistance; ///< Merging distance squared

    // physical constants
    const double gravity = 9.81; ///< Gravitational acceleration on earth (m/s^2)

    ///@brief Operations averaging methods
    enum class AveragingMethod
    {
        SimpleAveraging = 1,
        ClosestPoint = 2,
        Max = 3,
        Min = 4,
        InverseWeightDistance = 5,
        MinAbs = 6,
        KdTree = 7
    };

    /// @brief Interpolation locations
    enum class InterpolationLocation
    {
        Faces = 0,
        Nodes = 1,
        Edges = 2
    };

} // namespace meshkernel
