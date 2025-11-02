"""Specialized attention heads for multi-head transformer"""

from .specialized_heads import (
    MultiHeadAttentionCoordinator,
    ClaudeCog,
    ChatCoGPT,
    CoGrokX,
    CoGemini,
    AzureCog,
)

__all__ = [
    'MultiHeadAttentionCoordinator',
    'ClaudeCog',
    'ChatCoGPT',
    'CoGrokX',
    'CoGemini',
    'AzureCog',
]
