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

namespace meshkernelapi
{
    struct Mesh1DGeometry
    {
        int* branchid = nullptr;
        double* branch_offsets = nullptr;
        double* nodex = nullptr;
        double* nodey = nullptr;

        int* edge_nodes = nullptr;
        double* edge_idx = nullptr;
        double* edge_offsets = nullptr;
        double* edgex = nullptr;
        double* edgey = nullptr;

        void* nodeids = nullptr;
        void* nodelongnames = nullptr;
    };

} // namespace meshkernelapi