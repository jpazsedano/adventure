#!/usr/bin/python3
''' Herramienta para convertir los assets de alto nivel `*.yml` en un formato
    utilizable por el motor del juego '''

import argparse
import yaml
import json

# TODO Investigar si hay alguna librería que permita hacer la verificación rápida.
def checkInputIntegrity(rootNode):
    pass

def generateLevel(inputNode):
    level = {
        "levelName": inputNode["levelName"],
        "nextLevel": inputNode["nextLevel"]
    }

    level["objects"] = generateObjects(inputNode["map"]["rooms"])
    level["actions"] = generateActions(inputNode["map"]["rooms"])
    level["actions"].extend(generateStateActions(inputNode["stateTriggers"]))

    level["state"] = generateState(inputNode["state"], inputNode["stateTriggers"])
    level["map"] = generateMap(inputNode["map"])

    return level

# Las acciones están repartidas en las habitaciones en los niveles.
def generateActions(roomsNode, objects):
    # Inicializamos primer ID
    id = 1
    actions = []

    for room in roomsNode:
        if "objects" in room:
            for object in room["objects"]:
                for action in object["actions"]:
                    ac = {
                        "actionId": id,
                        "actionType": action["actionType"],
                        "actionText": action["actionText"],
                        "failedText": action["failedText"],
                        "conditions": action["conditions"]
                    }

                    for obj in objects:
                        if object["name"] == obj["name"]:
                            ac["object1Id"] = obj["id"]
                    if not "object1Id" in ac:
                        raise Exception(f"ID for Object 1 for {object["name"]} not found!")
                    
                    # el "doWith" se puede omitir simplemente.
                    if "doWith" in action:
                        for obj in objects:
                            if action["doWith"] == obj["name"]:
                                ac["object2Id"] = obj["id"]
                        if not "object2Id" in ac:
                            raise Exception(f"ID for Object 2 for {action["doWith"]} not found!")
                    else: # Si se omite, ponemos 0 que significa que no hay segundo objeto.
                        ac["object2Id"] = 0
                    
                    ac["triggers"] = []
                    for trigger in action["triggers"]:
                        pass

                    actions.append(ac)
                    id += 1

    return actions

# Las acciones
def generateStateActions(stateTriggersNode):
    pass

def generateState(stateNode, stateActionsNode):
    state = {}

    # El estado en realidad tiene el mismo formato.
    state["properties"] = stateNode
    state["onceActions"] = []
    state["repeatActions"] = []

    # Clasificamos los triggers según su tipo.
    for action in stateActionsNode:
        pass

    return state

def generateTrigger(triggerNode):
    pass

# Los objetos también están repartidos por las habitaciones.
def generateObjects(roomsNode):
    pass

def generateMap(mapNode):
    pass

def main():
    parser = argparse.ArgumentParser("Level generation tool")

    parser.add_argument("--input", "-i", required=True, help="The level description input file")
    parser.add_argument("--output", "-o", required=True, help="The output file to be loaded by the game")
    parser.add_argument("--format", "-f", default="yaml", choices=["yaml", "json"], help="The format of the output file")

    args = parser.parse_args()

    with open(args.input, "r") as f:
        inputObj = yaml.load(f, yaml.SafeLoader)

    level = generateLevel(inputObj)

    with open(args.output, "w") as fout:
        if args.format == "yaml":
            yaml.dump(level, fout, yaml.SafeDumper)
        elif args.format == "json":
            json.dump(level, fout)


# Si estamos ejecutando esto desde línea de comandos, ejecuta el main.
if __name__ == "__main__":
    main()
