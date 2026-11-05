# SPDX-License-Identifier: GPL-3.0-only
# Copyright (c) Fabian Schmidt and original contributors
# Copyright (c) RZ (@havanti) and contributors
# Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
# See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

from esphome.components import text_sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID, CONF_TYPE, ENTITY_CATEGORY_DIAGNOSTIC
from .. import truma_inetbox_ns, CONF_TRUMA_INETBOX_ID, TrumaINetBoxApp

DEPENDENCIES = ["truma_inetbox"]
CODEOWNERS = ["@havanti"]

TrumaVersionTextSensor = truma_inetbox_ns.class_(
    "TrumaVersionTextSensor", text_sensor.TextSensor, cg.Component
)

TrumaHeaterErrorTextSensor = truma_inetbox_ns.class_(
    "TrumaHeaterErrorTextSensor", text_sensor.TextSensor, cg.Component
)


def make_schema(class_type, heater=False):
    schema = text_sensor.text_sensor_schema(
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        icon="mdi:alert-circle-outline" if heater else "mdi:tag",
    ).extend({cv.GenerateID(): cv.declare_id(class_type)}).extend(cv.COMPONENT_SCHEMA)
    if heater:
        schema = schema.extend({
            cv.GenerateID(CONF_TRUMA_INETBOX_ID): cv.use_id(TrumaINetBoxApp),
        })
    return schema


# Existing configurations without type keep exposing the component version.
CONFIG_SCHEMA = cv.typed_schema(
    {
        "VERSION": make_schema(TrumaVersionTextSensor),
        "HEATER_ERROR_CODE": make_schema(TrumaHeaterErrorTextSensor, heater=True),
    },
    default_type="VERSION",
    upper=True,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    if config[CONF_TYPE] == "HEATER_ERROR_CODE":
        await cg.register_parented(var, config[CONF_TRUMA_INETBOX_ID])
