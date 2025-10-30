"""
Planetary Transformer Network

A planetary neural network where cities are neurons in a globe-spanning consciousness.
Each city operates as an attention head in a global transformer architecture.
"""

__version__ = "1.0.0"
__author__ = "Planetary Transformer Project"

from .core.city_attention_head import CityAsAttentionHead
from .core.economic_backprop import EconomicBackpropagation
from .layers.transformer_hierarchy import (
    HierarchicalTransformer,
    NeighborhoodTransformer,
    MetropolitanTransformer,
    ContinentalTransformer,
    PlanetaryTransformer,
)
from .heads.specialized_heads import (
    MultiHeadAttentionCoordinator,
    ClaudeCog,
    ChatCoGPT,
    CoGrokX,
    CoGemini,
    AzureCog,
)

__all__ = [
    'CityAsAttentionHead',
    'EconomicBackpropagation',
    'HierarchicalTransformer',
    'NeighborhoodTransformer',
    'MetropolitanTransformer',
    'ContinentalTransformer',
    'PlanetaryTransformer',
    'MultiHeadAttentionCoordinator',
    'ClaudeCog',
    'ChatCoGPT',
    'CoGrokX',
    'CoGemini',
    'AzureCog',
]
