
Qt library for http://eyes.nasa.gov/dsn (DSN) downloads catalog and
data XML and transforms content into maps and lists.

  Status

    Main.cpp runs well, but the data is not current.

  Operation

    Fetches the configuration catalog and data set by a call to
    DSNL::init, and then subsequently polls the data file for each
    call to DSNL::update.

    The command line driver, Main.cpp, prints a subset of the
    retrieved data sets.

  Package

    Files DSNL*.{h,cpp}

      Fetch XML and bind to data objects.

      DSNL                -- Head of library
      DSNLConfig          -- Runtime catalog map
      DSNLData            -- Live data lists
      DSMLXml             -- Network client common to Config and Data

    Files HTTPStream*.{h,cpp}

      A simple HTTP client.

      HTTPStreamClient    -- TCP socket 
      HTTPStreamRequest   -- read/write socket
      HTTPStreamResponse  -- read/write socket

    Files Main.{h,cpp}

      Example driver for command line.

