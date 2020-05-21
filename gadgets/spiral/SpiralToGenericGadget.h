#ifndef SpiralToGenericGadget_H
#define SpiralToGenericGadget_H
#pragma once

#include "gadgetron_spiral_export.h"
#include "Gadget.h"
#include "GadgetMRIHeaders.h"
#include "hoNDArray.h"
#include "TrajectoryParameters.h"

#include <ismrmrd/ismrmrd.h>
#include <complex>
#include <boost/shared_ptr.hpp>
#include <ismrmrd/xml.h>
#include <boost/optional.hpp>

namespace Gadgetron {

    class EXPORTGADGETS_SPIRAL SpiralToGenericGadget :
            public Gadget2<ISMRMRD::AcquisitionHeader, hoNDArray<std::complex<float> > > {

    public:
        GADGET_DECLARE(SpiralToGenericGadget);

        SpiralToGenericGadget();

        virtual ~SpiralToGenericGadget();

    protected:

        virtual int process_config(ACE_Message_Block *mb);

        virtual int process(GadgetContainerMessage<ISMRMRD::AcquisitionHeader> *m1,
                            GadgetContainerMessage<hoNDArray<std::complex<float> > > *m2);

        GADGET_PROPERTY(spiral_rotations, long, "Spiral rotations", 0);
        GADGET_PROPERTY(vds_factor, double, "Percentage reduction 2-fov vds design", 100);  

    private:

        bool prepared_;

        int samples_to_skip_start_;
        int samples_to_skip_end_;
        hoNDArray<float> trajectory_and_weights;
        Spiral::TrajectoryParameters trajectory_parameters;
        void prepare_trajectory(const ISMRMRD::AcquisitionHeader &acq_header);

    };
}
#endif //SpiralToGenericGadget_H
