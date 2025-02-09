RGB
===

Register Listing for RGB
------------------------

+----------------------------+------------------------------+
| Register                   | Address                      |
+============================+==============================+
| :ref:`RGB_DAT <RGB_DAT>`   | :ref:`0xe0006800 <RGB_DAT>`  |
+----------------------------+------------------------------+
| :ref:`RGB_ADDR <RGB_ADDR>` | :ref:`0xe0006804 <RGB_ADDR>` |
+----------------------------+------------------------------+
| :ref:`RGB_CTRL <RGB_CTRL>` | :ref:`0xe0006808 <RGB_CTRL>` |
+----------------------------+------------------------------+
| :ref:`RGB_RAW <RGB_RAW>`   | :ref:`0xe000680c <RGB_RAW>`  |
+----------------------------+------------------------------+

RGB_DAT
^^^^^^^

`Address: 0xe0006800 + 0x0 = 0xe0006800`

    This is the value for the ``SB_LEDDA_IP.DAT`` register.  It is directly written
    into the ``SB_LEDDA_IP`` hardware block, so you should refer to
    http://www.latticesemi.com/view_document?document_id=50668. The contents of this
    register are written to the address specified in ``ADDR`` immediately upon
    writing this register.

    .. wavedrom::
        :caption: RGB_DAT

        {
            "reg": [
                {"name": "dat[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


RGB_ADDR
^^^^^^^^

`Address: 0xe0006800 + 0x4 = 0xe0006804`

    This register is directly connected to ``SB_LEDDA_IP.ADDR``.  This register
    controls the address that is updated whenever ``DAT`` is written.  Writing to
    this register has no immediate effect -- data isn't written until the ``DAT``
    register is written.

    .. wavedrom::
        :caption: RGB_ADDR

        {
            "reg": [
                {"name": "addr[3:0]", "bits": 4},
                {"bits": 4},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


RGB_CTRL
^^^^^^^^

`Address: 0xe0006800 + 0x8 = 0xe0006808`

    Control logic for the RGB LED and LEDDA hardware PWM LED block.

    .. wavedrom::
        :caption: RGB_CTRL

        {
            "reg": [
                {"name": "exe",  "bits": 1},
                {"name": "curren",  "bits": 1},
                {"name": "rgbleden",  "bits": 1},
                {"name": "rraw",  "bits": 1},
                {"name": "graw",  "bits": 1},
                {"name": "braw",  "bits": 1},
                {"bits": 2}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+----------+---------------------------------------------------------------------------------+
| Field | Name     | Description                                                                     |
+=======+==========+=================================================================================+
| [0]   | EXE      | Connected to ``SB_LEDDA_IP.LEDDEXE``.  Set this to ``1`` to enable the fading   |
|       |          | pattern.                                                                        |
+-------+----------+---------------------------------------------------------------------------------+
| [1]   | CURREN   | Connected to ``SB_RGBA_DRV.CURREN``.  Set this to ``1`` to enable the current   |
|       |          | source.                                                                         |
+-------+----------+---------------------------------------------------------------------------------+
| [2]   | RGBLEDEN | Connected to ``SB_RGBA_DRV.RGBLEDEN``.  Set this to ``1`` to enable the RGB PWM |
|       |          | control logic.                                                                  |
+-------+----------+---------------------------------------------------------------------------------+
| [3]   | RRAW     | Set this to ``1`` to enable raw control of the red LED via the ``RAW.R``        |
|       |          | register.                                                                       |
+-------+----------+---------------------------------------------------------------------------------+
| [4]   | GRAW     | Set this to ``1`` to enable raw control of the green LED via the ``RAW.G``      |
|       |          | register.                                                                       |
+-------+----------+---------------------------------------------------------------------------------+
| [5]   | BRAW     | Set this to ``1`` to enable raw control of the blue LED via the ``RAW.B``       |
|       |          | register.                                                                       |
+-------+----------+---------------------------------------------------------------------------------+

RGB_RAW
^^^^^^^

`Address: 0xe0006800 + 0xc = 0xe000680c`

    Normally the hardware ``SB_LEDDA_IP`` block controls the brightness of the LED,
    creating a gentle fading pattern.  However, by setting the appropriate bit in
    ``CTRL``, it is possible to manually control the three individual LEDs.

    .. wavedrom::
        :caption: RGB_RAW

        {
            "reg": [
                {"name": "r",  "bits": 1},
                {"name": "g",  "bits": 1},
                {"name": "b",  "bits": 1},
                {"bits": 5}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+----------------------------------------------------------+
| Field | Name | Description                                              |
+=======+======+==========================================================+
| [0]   | R    | Raw value for the red LED when ``CTRL.RRAW`` is ``1``.   |
+-------+------+----------------------------------------------------------+
| [1]   | G    | Raw value for the green LED when ``CTRL.GRAW`` is ``1``. |
+-------+------+----------------------------------------------------------+
| [2]   | B    | Raw value for the blue LED when ``CTRL.BRAW`` is ``1``.  |
+-------+------+----------------------------------------------------------+

