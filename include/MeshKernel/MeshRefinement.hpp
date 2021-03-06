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

#include <vector>
#include <MeshKernel/SampleRefineParameters.hpp>
#include <MeshKernel/InterpolationParameters.hpp>
#include <MeshKernel/Entities.hpp>
#include <MeshKernel/SpatialTrees.hpp>
#include <MeshKernel/AveragingInterpolation.hpp>

namespace meshkernel
{
    // Forward declarations
    class Mesh;
    class Polygons;

    /// @brief A class used to refine a Mesh
    class MeshRefinement
    {
        enum class RefinementType
        {
            RidgeRefinement,
            WaveCourant,
            RefinementLevels
        };

    public:
        /// @brief Constructor
        /// @param[in] mesh The mesh to be refined
        /// @param[in] averaging The averaging interpolation to use
        explicit MeshRefinement(std::shared_ptr<Mesh> mesh, std::shared_ptr<AveragingInterpolation> averaging);

        /// @brief Constructor
        /// @param[in] mesh The mesh to be refined
        explicit MeshRefinement(std::shared_ptr<Mesh> mesh);

        /// @brief Refine a mesh (refinecellsandfaces2).
        ///
        /// Steps:
        /// 1. Masks the node to be refined (those inside a polygon)
        /// 2. Find the brother edges, the edge sharing a hanging node, FindBrotherEdges
        /// 3. Mask nodes at the polygon perimeter, ComputeNodeMaskAtPolygonPerimeter
        /// 4. Do refinement iterations
        ///    -# Find the brother edges, FindBrotherEdges
        ///    -# Compute the edge refinement mask based on samples, ComputeRefinementMasksFromSamples
        ///    -# Compute the edge refinement mask based on polygon, ComputeEdgesRefinementMask
        ///    -# Compute if a face should be split, ComputeIfFaceShouldBeSplit
        ///    -# Refine face by splitting edges, RefineFacesBySplittingEdges
        /// 5. Connect hanging nodes if requested, RemoveIsolatedHangingnodes, ConnectHangingNodes
        /// @param polygon The polygon where to perform refinement (option 2, refine in polygon)
        /// @param sampleRefineParameters Refinement based on samples parameters
        /// @param interpolationParameters Interpolation parameters
        void Refine(
            const Polygons& polygon,
            const meshkernelapi::SampleRefineParameters& sampleRefineParameters,
            const meshkernelapi::InterpolationParameters& interpolationParameters);

    private:
        /// @brief Finds if two edges are brothers, sharing an hanging node. Can be moved to Mesh
        void FindBrotherEdges();

        /// @brief Modifies m_mesh.m_nodeMask, all nodes of the faces intersecting the polygon perimeter will get value of -2 (set_initial_mask)
        ///        The mask value of the other nodes will not be modified.
        void ComputeNodeMaskAtPolygonPerimeter();

        /// @brief Computes the edge and face refinement mask from sample values (compute_jarefine_poly)
        /// @param samples The sample to use for computing masking
        void ComputeRefinementMasksFromSamples();

        /// @brief Computes the number of edges that should be refined in a face (compute_jarefine_poly)
        ///        Face nodes, edge and edge lengths are stored in local caches. See Mesh.FaceClosedPolygon method
        /// @param numPolygonNodes The number of face nodes
        /// @param samples The samples to use for refinement
        /// @param refineEdgeCache 1 if the edge should be refined, 0 otherwise
        /// @param numEdgesToBeRefined The computed number of edges to refined
        void ComputeEdgesRefinementMaskFromSamples(int face,
                                                   std::vector<int>& refineEdgeCache,
                                                   int& numEdgesToBeRefined);

        /// Computes the edge refinement mask (comp_jalink)
        /// @returns If the method succeeded
        void ComputeEdgesRefinementMask();

        /// @brief Finds the hanging nodes in a face (find_hangingnodes)
        /// @param faceIndex
        /// @param numHangingEdges
        /// @param numHangingNodes
        /// @param numEdgesToRefine
        void FindHangingNodes(int face,
                              int& numHangingEdges,
                              int& numHangingNodes,
                              int& numEdgesToRefine);

        /// Remove isolated hanging nodes(remove_isolated_hanging_nodes)
        /// @returns Number of removed isolated hanging nodes
        [[nodiscard]] int RemoveIsolatedHangingnodes();

        /// @brief Connect the hanging nodes with triangles (connect_hanging_nodes)
        void ConnectHangingNodes();

        /// @brief Smooth the face refinement mask (smooth_jarefine)
        void SmoothEdgeRefinementMask() const;

        /// @brief Computes m_faceMask, if a face must be split later on (split_cells)
        void ComputeIfFaceShouldBeSplit();

        /// @brief The refinement operation by splitting the face (refine_cells)
        /// @param[in] numEdgesBeforeRefinemet Number of edges before the refinement
        void RefineFacesBySplittingEdges(int numEdgesBeforeRefinement);

        /// Compute the refinement value at the face center of mass
        /// @param[in] numPolygonNodes The number of polygon nodes
        /// @param[in] samples The number of samples
        /// @param[in] averagingMethod The averaging method to used
        /// @param[in] centerOfMass The face center of mass
        /// @returns The refinement value at the face center of mass
        [[nodiscard]] double ComputeFaceRefinementFromSamples(int numPolygonNodes,
                                                              const std::vector<Sample>& samples,
                                                              AveragingInterpolation::Method averagingMethod,
                                                              Point centerOfMass);
        /// The sample node RTree
        SpatialTrees::RTree m_samplesRTree;

        std::vector<int> m_faceMask;     ///< Refine face without hanging nodes (1), refine face with hanging nodes (2), do not refine cell at all (0) or refine face outside polygon (-2)
        std::vector<int> m_edgeMask;     ///< If 0, edge is not split
        std::vector<int> m_brotherEdges; ///< The index of the brother edge for each edge

        /// Local caches
        std::vector<bool> m_isHangingNodeCache;   ///< Cache for maintaining if node is hanging
        std::vector<bool> m_isHangingEdgeCache;   ///< Cache for maintaining if edge is hanging
        std::vector<Point> m_polygonNodesCache;   ///< Cache for maintaining polygon nodes
        std::vector<int> m_localNodeIndicesCache; ///< Cache for maintaining local node indices
        std::vector<int> m_edgeIndicesCache;      ///< Cache for maintaining edge indices

        double m_deltaTimeMaxCourant = 0.0;         ///< The maximum courant number for delta time
        double m_minimumFaceSize = 5e4;             ///< Minimum face size
        bool m_directionalRefinement = false;       ///< Whether there is directional refinement
        bool m_refineOutsideFace = false;           ///< Whether to refine outside the face
        bool m_connectHangingNodes = true;          ///< Whether to connect hanging nodes
        bool m_refineIntersectedFaces = false;      ///< Whether to refine intersected faces
        int m_maxNumberOfRefinementIterations = 10; ///< Maximum number of refinement iterations

        RefinementType m_refinementType; /// The type of refinement to use

        std::shared_ptr<Mesh> m_mesh;
        std::shared_ptr<AveragingInterpolation> m_averaging = nullptr;
    };
} // namespace meshkernel
