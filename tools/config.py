"""Local paths to the retail binaries and symbols (config.local.json, never committed)."""
import json
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent


def load_config():
    path = REPO / "config.local.json"
    if not path.exists():
        raise SystemExit(f"missing {path}: copy config.example.json and fill in the paths")
    return json.loads(path.read_text())
