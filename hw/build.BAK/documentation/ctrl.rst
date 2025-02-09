CTRL
====

Register Listing for CTRL
-------------------------

+--------------------------------------------+--------------------------------------+
| Register                                   | Address                              |
+============================================+======================================+
| :ref:`CTRL_RESET <CTRL_RESET>`             | :ref:`0xe0000000 <CTRL_RESET>`       |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_SCRATCH3 <CTRL_SCRATCH3>`       | :ref:`0xe0000004 <CTRL_SCRATCH3>`    |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_SCRATCH2 <CTRL_SCRATCH2>`       | :ref:`0xe0000008 <CTRL_SCRATCH2>`    |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_SCRATCH1 <CTRL_SCRATCH1>`       | :ref:`0xe000000c <CTRL_SCRATCH1>`    |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_SCRATCH0 <CTRL_SCRATCH0>`       | :ref:`0xe0000010 <CTRL_SCRATCH0>`    |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_BUS_ERRORS3 <CTRL_BUS_ERRORS3>` | :ref:`0xe0000014 <CTRL_BUS_ERRORS3>` |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_BUS_ERRORS2 <CTRL_BUS_ERRORS2>` | :ref:`0xe0000018 <CTRL_BUS_ERRORS2>` |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_BUS_ERRORS1 <CTRL_BUS_ERRORS1>` | :ref:`0xe000001c <CTRL_BUS_ERRORS1>` |
+--------------------------------------------+--------------------------------------+
| :ref:`CTRL_BUS_ERRORS0 <CTRL_BUS_ERRORS0>` | :ref:`0xe0000020 <CTRL_BUS_ERRORS0>` |
+--------------------------------------------+--------------------------------------+

CTRL_RESET
^^^^^^^^^^

`Address: 0xe0000000 + 0x0 = 0xe0000000`

    Write a ``1`` to this register to reset the SoC.

    .. wavedrom::
        :caption: CTRL_RESET

        {
            "reg": [
                {"name": "reset", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_SCRATCH3
^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x4 = 0xe0000004`

    Bits 24-31 of `CTRL_SCRATCH`. Use this register as a scratch space to verify
    that software read/write accesses to the Wishbone/CSR bus are working correctly.
    The initial reset value of 0x1234578 can be used to verify endianness.

    .. wavedrom::
        :caption: CTRL_SCRATCH3

        {
            "reg": [
                {"name": "scratch[31:24]", "attr": 'reset: 18', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_SCRATCH2
^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x8 = 0xe0000008`

    Bits 16-23 of `CTRL_SCRATCH`.

    .. wavedrom::
        :caption: CTRL_SCRATCH2

        {
            "reg": [
                {"name": "scratch[23:16]", "attr": 'reset: 52', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_SCRATCH1
^^^^^^^^^^^^^

`Address: 0xe0000000 + 0xc = 0xe000000c`

    Bits 8-15 of `CTRL_SCRATCH`.

    .. wavedrom::
        :caption: CTRL_SCRATCH1

        {
            "reg": [
                {"name": "scratch[15:8]", "attr": 'reset: 86', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_SCRATCH0
^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x10 = 0xe0000010`

    Bits 0-7 of `CTRL_SCRATCH`.

    .. wavedrom::
        :caption: CTRL_SCRATCH0

        {
            "reg": [
                {"name": "scratch[7:0]", "attr": 'reset: 120', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_BUS_ERRORS3
^^^^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x14 = 0xe0000014`

    Bits 24-31 of `CTRL_BUS_ERRORS`. Total number of Wishbone bus errors (timeouts)
    since start.

    .. wavedrom::
        :caption: CTRL_BUS_ERRORS3

        {
            "reg": [
                {"name": "bus_errors[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_BUS_ERRORS2
^^^^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x18 = 0xe0000018`

    Bits 16-23 of `CTRL_BUS_ERRORS`.

    .. wavedrom::
        :caption: CTRL_BUS_ERRORS2

        {
            "reg": [
                {"name": "bus_errors[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_BUS_ERRORS1
^^^^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x1c = 0xe000001c`

    Bits 8-15 of `CTRL_BUS_ERRORS`.

    .. wavedrom::
        :caption: CTRL_BUS_ERRORS1

        {
            "reg": [
                {"name": "bus_errors[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


CTRL_BUS_ERRORS0
^^^^^^^^^^^^^^^^

`Address: 0xe0000000 + 0x20 = 0xe0000020`

    Bits 0-7 of `CTRL_BUS_ERRORS`.

    .. wavedrom::
        :caption: CTRL_BUS_ERRORS0

        {
            "reg": [
                {"name": "bus_errors[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


