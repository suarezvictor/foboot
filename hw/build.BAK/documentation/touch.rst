TOUCH
=====

Register Listing for TOUCH
--------------------------

+----------------------------+------------------------------+
| Register                   | Address                      |
+============================+==============================+
| :ref:`TOUCH_O <TOUCH_O>`   | :ref:`0xe0005800 <TOUCH_O>`  |
+----------------------------+------------------------------+
| :ref:`TOUCH_OE <TOUCH_OE>` | :ref:`0xe0005804 <TOUCH_OE>` |
+----------------------------+------------------------------+
| :ref:`TOUCH_I <TOUCH_I>`   | :ref:`0xe0005808 <TOUCH_I>`  |
+----------------------------+------------------------------+

TOUCH_O
^^^^^^^

`Address: 0xe0005800 + 0x0 = 0xe0005800`

    Output values for pads 1-4

    .. wavedrom::
        :caption: TOUCH_O

        {
            "reg": [
                {"name": "o[3:0]", "bits": 4},
                {"bits": 4},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TOUCH_OE
^^^^^^^^

`Address: 0xe0005800 + 0x4 = 0xe0005804`

    Output enable control for pads 1-4

    .. wavedrom::
        :caption: TOUCH_OE

        {
            "reg": [
                {"name": "oe[3:0]", "bits": 4},
                {"bits": 4},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


TOUCH_I
^^^^^^^

`Address: 0xe0005800 + 0x8 = 0xe0005808`

    Input value for pads 1-4

    .. wavedrom::
        :caption: TOUCH_I

        {
            "reg": [
                {"name": "i[3:0]", "bits": 4},
                {"bits": 4},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


