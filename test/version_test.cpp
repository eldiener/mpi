// Copyright (C) 2013 Alain Miniussi <alain.miniussi@oca.eu>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// test mpi version

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/test/minimal.hpp>
#include <iostream>

namespace mpi = boost::mpi;

void
test_version(mpi::communicator const& comm) {
#if defined(MPI_VERSION)
  int mpi_version    = MPI_VERSION;
  int mpi_subversion = MPI_SUBVERSION;
#else
  int mpi_version = 0;
  int mpi_subversion = 0;
#endif
  
  std::pair<int,int> version = mpi::environment::version();
  if (comm.rank() == 0) {
    std::cout << "MPI Version: " << version.first << ',' << version.second << '\n';
  }
  BOOST_CHECK(version.first == mpi_version);
  BOOST_CHECK(version.second == mpi_subversion);
}

std::string
yesno(bool b) {
  return b ? std::string("yes") : std::string("no");
}

void
report_features(mpi::communicator const& comm) {
#if defined(BOOST_MPI_NO_IMPROBE)
  bool has_working_improbe = false;
#else
  bool has_working_improbe = true;
#endif
  if (comm.rank() == 0) {
    std::cout << "Assuming working MPI_Improbe:" << yesno(has_working_improbe) << '\n';
  }
}

int
test_main(int argc, char* argv[]) {
  mpi::environment env(argc,argv);
  mpi::communicator world;

  test_version(world);
  report_features(world);
    
  return 0;
}
